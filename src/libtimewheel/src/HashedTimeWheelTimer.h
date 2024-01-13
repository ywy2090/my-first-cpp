#pragma once
#include "liblogger/src/Common.h"
#include "libtimewheel/src/HashedTimeWheelTimer.h"
#include "libtimewheel/src/HashedTimeWheelTimerTask.h"
#include "libtimewheel/src/HashedWheelTimerList.h"
#include "libtimewheel/src/TimeWheelTimer.h"
#include "libtimewheel/src/excutor/Excutor.h"

#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <future>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

namespace octopus::timewheel
{
class HashedTimeWheelTimer : public TimeWheelTimer,
                             public std::enable_shared_from_this<HashedTimeWheelTimer>
{
public:
    constexpr static uint32_t defaultTimeWheelStepMicroSec = 500;

    HashedTimeWheelTimer(const HashedTimeWheelTimer&) = delete;
    HashedTimeWheelTimer(HashedTimeWheelTimer&&) = delete;

    HashedTimeWheelTimer& operator=(const HashedTimeWheelTimer&) = delete;
    HashedTimeWheelTimer& operator=(HashedTimeWheelTimer&&) = delete;
    HashedTimeWheelTimer() : HashedTimeWheelTimer(defaultTimeWheelStepMicroSec) {}
    HashedTimeWheelTimer(uint32_t _timeWheelStepMicroSec)
      : m_taskExecutor(std::shared_ptr<executor::Executor>(new executor::DefaultExecutor())),
        m_timeWheelStepMicroSec(_timeWheelStepMicroSec)
    {}
    ~HashedTimeWheelTimer() override { stop(); }

private:
    // loop
    void runLoop();

    // loop once
    void runOnceLoop();
    void processWaitingTasks();
    void innerTaskForStatReport();

    void stopThread()
    {
        // stop thread
        if (m_runThread && m_runThread->joinable())
        {
            m_runThread->join();
        }
    }

public:
    static uint32_t calcShouldWaitRound(uint32_t _shouldWaitMicroSec,
        uint32_t _timeWheelStepMicroSec, uint32_t _hashedTimeWheelTimerHashSize)
    {
        auto shouldWaitRound = (uint32_t)_shouldWaitMicroSec /
                               (_timeWheelStepMicroSec * _hashedTimeWheelTimerHashSize);
        return shouldWaitRound;
    }

    static uint32_t calcHashBucketIndex(uint32_t _shouldWaitMicroSec,
        uint32_t _timeWheelStepMicroSec, uint32_t _hashedTimeWheelTimerHashSize,
        uint32_t _currentHashBucketIndex)
    {
        uint32_t hashBucketIndex =
            (((_shouldWaitMicroSec % (_timeWheelStepMicroSec * _hashedTimeWheelTimerHashSize)) /
                 _timeWheelStepMicroSec) +
                _currentHashBucketIndex + 1) %
            _hashedTimeWheelTimerHashSize;
        return hashBucketIndex;
    }

    inline void nextHashBucketIndex()
    {
        m_totalRunRound++;
        m_currentHashBucketIndex =
            (m_currentHashBucketIndex + 1) % m_hashedTimeWheelTimerHash.size();
    }

public:
    /**
     * @brief create new timewheel task
     *
     * @param _funcTask
     * @param _delayMS
     * @return TimeWheelTimerTask::Ptr
     */
    TimeWheelTimerTask::Ptr newTask(std::function<void()> _funcTask, uint32_t _delayMS) override;

    void start() override
    {
        bool expect = false;
        bool result = true;
        if (!m_running.compare_exchange_strong(expect, result))
        {
            LOG_INFO(LOG_MODULE("TIMEWHEEL") << " timewheel has been started");
            return;
        }

        m_startTimePoint = std::chrono::steady_clock::now();
        m_runThread = std::make_unique<std::thread>(&HashedTimeWheelTimer::runLoop, this);
        m_runThreadStartFlag.get_future().get();
        innerTaskForStatReport();

        LOG_INFO(LOG_MODULE("TIMEWHEEL")
                 << " start timewheel" << LOG_KV("timeWheelStepMicroSec", m_timeWheelStepMicroSec));
    }
    void stop() override
    {
        bool expect = true;
        bool result = false;
        if (m_running.compare_exchange_strong(expect, result))
        {
            stopThread();
            LOG_INFO(LOG_MODULE("TIMEWHEEL") << " stop timewheel");
        }
    }

private:
    std::atomic<bool> m_running{false};
    // flag for m_runThread start
    std::promise<bool> m_runThreadStartFlag;
    // thread for run loop
    std::unique_ptr<std::thread> m_runThread;
    // executor for task run
    std::shared_ptr<executor::Executor> m_taskExecutor;

    // start time for timer
    std::chrono::steady_clock::time_point m_startTimePoint;

    u_int64_t m_totalRunRound = 0;

    const uint32_t m_timeWheelStepMicroSec;

    // TODO: make it config item
    constexpr static uint32_t defaultHashedTimeWheelTimerHashSize = 1024;
    std::size_t m_currentHashBucketIndex = 0;
    std::array<HashedWheelTimerList, defaultHashedTimeWheelTimerHashSize>
        m_hashedTimeWheelTimerHash{};

    std::mutex x_waitingTaskQueue;
    std::list<HashedTimeWheelTimerTask::Ptr> m_waitingTaskQueue;
};
}  // namespace octopus::timewheel