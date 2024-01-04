#pragma once

#include "ObjectRefCount.h"
#include "TimeWheelTimer.h"
#include <atomic>
#include <chrono>
#include <iostream>

namespace octopus
{
namespace timewheel
{

// impl TimeWheelTimerTask for HashedTimeWheelTimer
class HashedTimeWheelTimerTask : public TimeWheelTimerTask,
                                 public objref::ObjectRefCount<HashedTimeWheelTimerTask>
{
public:
    using Ptr = std::shared_ptr<HashedTimeWheelTimerTask>;

    HashedTimeWheelTimerTask(const HashedTimeWheelTimerTask&) = delete;
    HashedTimeWheelTimerTask(HashedTimeWheelTimerTask&&) = delete;
    HashedTimeWheelTimerTask& operator=(const HashedTimeWheelTimerTask&) = delete;
    HashedTimeWheelTimerTask&& operator=(HashedTimeWheelTimerTask&&) = delete;

    ~HashedTimeWheelTimerTask() override
    {
        //  std::cout << "[DELOBJ][HashedTimeWheelTimerTask] this= " << this << std::endl;
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
      : m_task(std::move(_task)), m_delayMS(_delayMS), m_inTimePoint(_inTimePoint)
    {
        //  std::cout << "[NEWOBJ][HashedTimeWheelTimerTask] this= " << this << std::endl;
    }

    // cancel the task
    bool cancel() override
    {
        int expect = waiting;
        return m_taskState.compare_exchange_strong(expect, canceled);
    }

    bool isCanceled() const { return m_taskState.load(std::memory_order_acquire) == canceled; }

    // reset task state
    void setState(State _state) { m_taskState = _state; }
    bool isWaiting() const { return m_taskState.load(std::memory_order_acquire) == waiting; }
    bool isProcessing() const { return m_taskState.load(std::memory_order_acquire) == processing; }
    bool isFinished() const { return m_taskState.load(std::memory_order_acquire) == finished; }

    // task waiting time
    int32_t waitingTimeMilli()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            m_beginProcessTimePoint - m_inTimePoint)
            .count();
    }

    // task exec time
    int32_t execTimeMilli()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            m_endProcessTimePoint - m_beginProcessTimePoint)
            .count();
    }

    const std::function<void()>& task() const { return m_task; }
    uint32_t delayMS() const { return m_delayMS; }

    uint32_t leftRoundToExec() const { return m_leftRoundToExec; }
    uint32_t hashEntryIndex() const { return m_hashEntryIndex; }
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
    uint32_t m_hashEntryIndex = (uint32_t)-1;
    //
    std::chrono::steady_clock::time_point m_inTimePoint;
    //
    std::chrono::steady_clock::time_point m_beginProcessTimePoint;
    //
    std::chrono::steady_clock::time_point m_endProcessTimePoint;
};
}  // namespace timewheel
}  // namespace octopus