#pragma once
#include "HashedTimeWheelTimer.h"
#include "HashedTimeWheelTimerTask.h"
#include "HashedWheelTimerList.h"
#include "TimeWheelTimer.h"

#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

namespace octopus
{

class HashedTimeWheelTimer : public TimeWheelTimer
{
public:
    constexpr static uint32_t defaultTimeStepUS = 500;

    HashedTimeWheelTimer(const HashedTimeWheelTimer&) = delete;
    HashedTimeWheelTimer(HashedTimeWheelTimer&&) = delete;

    HashedTimeWheelTimer& operator=(const HashedTimeWheelTimer&) = delete;
    HashedTimeWheelTimer& operator=(HashedTimeWheelTimer&&) = delete;
    HashedTimeWheelTimer() : HashedTimeWheelTimer(defaultTimeStepUS) {}
    HashedTimeWheelTimer(uint32_t _timeStepUS) : m_timeStepUS(_timeStepUS)
    {
        std::cout << "[NEWOBJ][HashedTimeWheelTimer] this= " << this << std::endl;
    }
    ~HashedTimeWheelTimer() override
    {
        std::cout << "[DELOBJ][HashedTimeWheelTimer] this= " << this << std::endl;
        stop();
    }

private:
    // loop
    void runLoop();

    // loop once
    void runOnceLoop();
    void processWaitingTasks();

    void stopThread()
    {
        // stop thread
        if (m_runThread && m_runThread->joinable())
        {
            m_runThread->join();
        }
    }

public:
    // construct timer task
    TimeWheelTimerTask::Ptr newTask(std::function<void()> _funcTask, uint32_t _delayMS) override
    {
        auto taskPtr = std::make_shared<HashedTimeWheelTimerTask>(std::move(_funcTask), _delayMS);

        auto nowTimePoint = std::chrono::steady_clock::now();
        // auto shouldExecTimePoint = nowTimePoint + std::chrono::milliseconds(_delayMS);

        taskPtr->m_inTimePoint = nowTimePoint;

        {
            std::lock_guard<std::mutex> lock(x_waitingTaskQueue);
            m_waitingTaskQueue.push_back(taskPtr);
        }

        std::cout << " ==> newTask" << std::endl;

        return taskPtr;
    }

    void start()
    {
        if (m_running)
        {
            return;
        }

        m_running = true;
        m_startTimePoint = std::chrono::steady_clock::now();
        m_runThread = std::make_unique<std::thread>(&HashedTimeWheelTimer::runLoop, this);
    }
    void stop() { stopThread(); }

private:
    // thread for run loop
    std::unique_ptr<std::thread> m_runThread;
    std::atomic<bool> m_running{false};
    std::chrono::steady_clock::time_point m_startTimePoint;

    std::once_flag m_startFlag;
    uint32_t m_timeStepUS;

    constexpr static uint32_t defaultHashedTimeWheelTimerHashSize = 1024;
    std::size_t m_currentEntryIndex = 0;
    std::array<HashedWheelTimerList, defaultHashedTimeWheelTimerHashSize>
        m_hashedTimeWheelTimerHash{};

    std::mutex x_waitingTaskQueue;
    std::list<HashedTimeWheelTimerTask::Ptr> m_waitingTaskQueue;
};
}  // namespace octopus