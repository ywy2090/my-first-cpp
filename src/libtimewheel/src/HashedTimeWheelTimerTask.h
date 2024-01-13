#pragma once

#include "Common.h"
#include "TimeWheelTimer.h"
#include "liblogger/src/Logger.h"
#include "libmemleak/src/ObjectAllocatorCounter.h"
#include "libmemleak/src/ObjectAllocatorMonitor.h"
#include <atomic>
#include <chrono>
#include <iostream>

namespace octopus::timewheel
{

// impl TimeWheelTimerTask for HashedTimeWheelTimer
class HashedTimeWheelTimerTask : public TimeWheelTimerTask,
                                 public memleak::ObjectAllocatorCounter<HashedTimeWheelTimerTask>
{
public:
    using Ptr = std::shared_ptr<HashedTimeWheelTimerTask>;

    HashedTimeWheelTimerTask(const HashedTimeWheelTimerTask&) = delete;
    HashedTimeWheelTimerTask(HashedTimeWheelTimerTask&&) = delete;
    HashedTimeWheelTimerTask& operator=(const HashedTimeWheelTimerTask&) = delete;
    HashedTimeWheelTimerTask&& operator=(HashedTimeWheelTimerTask&&) = delete;

    ~HashedTimeWheelTimerTask() override
    {
        LOG_DEBUG("[DELOBJ][HashedTimeWheelTimerTask] " << LOG_KV("this", this));
    }

    enum State
    {
        waiting = 1,
        canceled = 2,
        processing = 3,
        finished = 4
    };

    HashedTimeWheelTimerTask(std::function<void()> _task, uint32_t _delayMS,
        std::chrono::steady_clock::time_point _inTimePoint = std::chrono::steady_clock::now())
      : m_task(std::move(_task)), m_delayMS(_delayMS), m_createTimePoint(_inTimePoint)
    {
        LOG_DEBUG("[NEWOBJ][HashedTimeWheelTimerTask] " << LOG_KV("this", this));
    }


    // cancel the task
    bool cancel() override
    {
        int expect = waiting;
        return m_taskState.compare_exchange_strong(expect, canceled);
    }

    // reset task state
    void setState(State _state) { m_taskState = _state; }

    bool isCanceled() const { return m_taskState.load(std::memory_order_acquire) == canceled; }
    bool isWaiting() const { return m_taskState.load(std::memory_order_acquire) == waiting; }
    bool isProcessing() const { return m_taskState.load(std::memory_order_acquire) == processing; }
    bool isFinished() const { return m_taskState.load(std::memory_order_acquire) == finished; }

    // task waiting time
    int64_t waitingTimeMilli()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            m_beginProcessTimePoint - m_createTimePoint)
            .count();
    }

    // task exec time
    int64_t execTimeMilli()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            m_endProcessTimePoint - m_beginProcessTimePoint)
            .count();
    }

    // total elapsed time from task create
    int64_t elapsedTimeMilli()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            m_endProcessTimePoint - m_createTimePoint)
            .count();
    }

    const std::function<void()>& task() const { return m_task; }
    uint32_t delayMS() const { return m_delayMS; }

    uint32_t leftRoundToExec() const { return m_leftRoundToExec; }
    uint32_t currentHashBucketIndex() const { return m_currentHashBucketIndex; }
    void decrLeftRoundToExec() { m_leftRoundToExec--; }

    friend class HashedTimeWheelTimer;

private:
    // task state
    std::atomic<int> m_taskState{waiting};
    // task function
    std::function<void()> m_task;
    // left round to be executed
    uint32_t m_leftRoundToExec = 0;
    // task delay ms
    uint32_t m_delayMS;

    //
    uint32_t m_currentHashBucketIndex = (uint32_t)-1;
    //
    std::chrono::steady_clock::time_point m_createTimePoint;
    //
    std::chrono::steady_clock::time_point m_beginProcessTimePoint;
    //
    std::chrono::steady_clock::time_point m_endProcessTimePoint;
};
}  // namespace octopus::timewheel