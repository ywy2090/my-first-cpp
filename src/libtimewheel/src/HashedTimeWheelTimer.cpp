

#include "HashedTimeWheelTimer.h"

using namespace octopus;
using namespace octopus::timewheel;

// loop
void HashedTimeWheelTimer::runLoop()
{
    while (m_running)
    {
        runOnceLoop();

        if (!m_running)
        {
            break;
        }

        m_currentEntryIndex = (m_currentEntryIndex + 1) % m_hashedTimeWheelTimerHash.size();
        std::this_thread::sleep_for(std::chrono::microseconds(m_timeStepUS));
    }
}

// loop once
void HashedTimeWheelTimer::runOnceLoop()
{
    // handle waiting tasks
    processWaitingTasks();

    // handle task expired or canceled
    auto& hashedWheelTimerList = m_hashedTimeWheelTimerHash.at(m_currentEntryIndex);

    std::list<HashedWheelTimerNode::Ptr> removeTaskList;

    auto node = hashedWheelTimerList.head;
    while (node)
    {
        auto& task = node->task;

        if (!m_running)
        {
            break;
        }

        do
        {
            if (task->isCanceled())
            {
                removeTaskList.push_back(node);
                break;
            }

            uint32_t leftRound = task->leftRoundToExec();

            if (leftRound > 0)
            {
                task->decrLeftRoundToExec();
                break;
            }

            int expect = HashedTimeWheelTimerTask::State::waiting;
            int result = HashedTimeWheelTimerTask::State::processing;
            if (task->m_taskState.compare_exchange_strong(expect, result))
            {
                // TODO: exec task in independent thread pool
                task->m_beginProcessTimePoint = std::chrono::steady_clock::now();
                task->task()();
                task->m_endProcessTimePoint = std::chrono::steady_clock::now();
                // task->execTimeMilli();
                task->setState(HashedTimeWheelTimerTask::State::finished);
                removeTaskList.push_back(node);
            }
            else
            {
                // Note: task is cancelled
                assert(task->isCanceled());
            }
        } while (false);  // do

        node = node->next;
    }

    // remove node from task list
    for (auto& node : removeTaskList)
    {
        auto task = node->task;
        hashedWheelTimerList.eraseNode(node);
    }
}

void HashedTimeWheelTimer::processWaitingTasks()
{
    std::list<HashedTimeWheelTimerTask::Ptr> waitingTaskQueue;
    // move waiting tasks
    {
        std::lock_guard<std::mutex> lock(x_waitingTaskQueue);
        waitingTaskQueue = m_waitingTaskQueue;
        m_waitingTaskQueue.clear();
    }

    if (waitingTaskQueue.empty())
    {
        return;
    }

    for (auto& task : waitingTaskQueue)
    {
        if (task->isCanceled())
        {
            continue;
        }

        if (!m_running)
        {
            break;
        }

        auto shouldExecTimePoint = task->m_inTimePoint + std::chrono::milliseconds(task->m_delayMS);

        if (shouldExecTimePoint < m_startTimePoint)
        {
            shouldExecTimePoint = m_startTimePoint;
        }

        auto diffMicroSec = std::chrono::duration_cast<std::chrono::microseconds>(
            shouldExecTimePoint - m_startTimePoint)
                                .count();
        // TODO: Fix this
        auto totalRound = diffMicroSec / (m_timeStepUS * defaultHashedTimeWheelTimerHashSize);
        task->m_leftRoundToExec = totalRound;
        uint32_t entryIndex =
            diffMicroSec % (m_timeStepUS * defaultHashedTimeWheelTimerHashSize) / m_timeStepUS;
        task->m_hashEntryIndex = entryIndex;
        m_hashedTimeWheelTimerHash.at(entryIndex).createNodeAndAppendNode(task);

        std::cout << " => Waiting tasks, diffMicroSec: " << diffMicroSec
                  << " totalRound: " << totalRound << " entryIndex: " << entryIndex << std::endl;
    }

    waitingTaskQueue.clear();
}
