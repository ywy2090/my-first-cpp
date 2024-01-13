

#include "libtimewheel/src/HashedTimeWheelTimer.h"
#include "liblogger/src/Common.h"
#include "liblogger/src/Logger.h"
#include "libtimewheel/src/excutor/Excutor.h"
#include <chrono>
#include <cstdint>
#include <exception>

using namespace octopus;
using namespace octopus::logger;
using namespace octopus::timewheel;

/**
 * @brief create new timewheel task
 *
 * @param _funcTask
 * @param _delayMS
 * @return TimeWheelTimerTask::Ptr
 */
TimeWheelTimerTask::Ptr HashedTimeWheelTimer::newTask(
    std::function<void()> _funcTask, uint32_t _delayMS)
{
    auto taskPtr = std::make_shared<HashedTimeWheelTimerTask>(std::move(_funcTask), _delayMS);
    // taskPtr->m_createTimePoint = std::chrono::steady_clock::now();

    {
        std::lock_guard<std::mutex> lock(x_waitingTaskQueue);
        m_waitingTaskQueue.push_back(taskPtr);
    }

    LOG_DEBUG(LOG_MODULE("TIMEWHEEL") << " newTask, delayMS: " << _delayMS);

    return taskPtr;
}

// loop
void HashedTimeWheelTimer::runLoop()
{
    m_runThreadStartFlag.set_value(true);

    while (m_running)
    {
        runOnceLoop();

        if (!m_running)
        {
            break;
        }

        nextHashBucketIndex();
        // sleep for next round
        std::this_thread::sleep_for(std::chrono::microseconds(m_timeWheelStepMicroSec));
    }
}

// loop once
void HashedTimeWheelTimer::runOnceLoop()
{
    // handle waiting tasks
    processWaitingTasks();

    // handle task expired or canceled
    auto& hashedWheelTimerList = m_hashedTimeWheelTimerHash.at(m_currentHashBucketIndex);

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
                auto taskExecutor = m_taskExecutor;
                m_taskExecutor->run([task, taskExecutor]() {
                    task->m_beginProcessTimePoint = std::chrono::steady_clock::now();
                    task->task()();
                    task->m_endProcessTimePoint = std::chrono::steady_clock::now();
                    LOG_INFO(LOG_MODULE("TIMEWHEEL")
                             << " task exec end"
                             << " ,exec time: " << task->execTimeMilli() << "ms"
                             << " ,elapsed time: " << task->elapsedTimeMilli() << "ms");
                    task->setState(HashedTimeWheelTimerTask::State::finished);
                });

                removeTaskList.push_back(node);
            }
            else
            {
                // Note: task is cancelled or processing
                assert(task->isCanceled() || task->isProcessing());
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

        // auto shouldExecTimePoint =
        //     task->m_createTimePoint + std::chrono::milliseconds(task->m_delayMS);

        // if (shouldExecTimePoint < m_startTimePoint)
        // {
        //     shouldExecTimePoint = m_startTimePoint;
        // }

        // task should wait time
        // auto shouldWaitMicroSec = std::chrono::duration_cast<std::chrono::microseconds>(
        //     shouldExecTimePoint - m_startTimePoint)
        //                               .count();

        // TODO: Fixed inaccurate timing accuracy
        uint32_t shouldWaitMicroSec = task->m_delayMS * 1000;
        auto shouldWaitRound = calcShouldWaitRound(
            shouldWaitMicroSec, m_timeWheelStepMicroSec, defaultHashedTimeWheelTimerHashSize);

        uint32_t hashBucketIndex = calcHashBucketIndex(shouldWaitMicroSec, m_timeWheelStepMicroSec,
            defaultHashedTimeWheelTimerHashSize, m_currentHashBucketIndex);

        task->m_leftRoundToExec = shouldWaitRound;
        task->m_currentHashBucketIndex = hashBucketIndex;
        m_hashedTimeWheelTimerHash.at(hashBucketIndex).createNodeAndAppendNode(task);

        LOG_INFO(LOG_MODULE("TIMEWHEEL")
                 << " => Waiting tasks " << LOG_KV("shouldWaitMicroSec", shouldWaitMicroSec)
                 << LOG_KV("shouldWaitRound", shouldWaitRound)
                 << LOG_KV("hashBucketIndex", hashBucketIndex));
    }

    waitingTaskQueue.clear();
}

void HashedTimeWheelTimer::innerTaskForStatReport()
{
    auto nowTimePoint = std::chrono::steady_clock::now();

    auto runSeconds =
        std::chrono::duration_cast<std::chrono::seconds>(nowTimePoint - m_startTimePoint).count();

    LOG_INFO(" => innerTaskForStatReport" LOG_KV("runSeconds", runSeconds)
             << LOG_KV("totalRunRound", m_totalRunRound)
             << LOG_KV("currentHashBucketIndex", m_currentHashBucketIndex));

    auto self = weak_from_this().lock();
    if (!self)
    {
        return;
    }

    self->newTask(
        [weakPtr = weak_from_this()]() {
            // auto weakPtr = weak_from_this();
            auto self = weakPtr.lock();
            if (self)
            {
                self->innerTaskForStatReport();
            }
        },
        10000);
}
