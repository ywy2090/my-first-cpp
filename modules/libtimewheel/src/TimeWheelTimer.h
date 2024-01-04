#pragma once

#include <functional>
#include <memory>

// interface for TimeWheelTimer
namespace octopus
{

// task for TimeWheelTimer
class TimeWheelTimerTask
{
public:
    using Ptr = std::shared_ptr<TimeWheelTimerTask>;
    TimeWheelTimerTask() = default;
    TimeWheelTimerTask(const TimeWheelTimerTask&) = delete;
    TimeWheelTimerTask(TimeWheelTimerTask&&) = delete;
    TimeWheelTimerTask& operator=(const TimeWheelTimerTask&) = delete;
    TimeWheelTimerTask&& operator=(TimeWheelTimerTask&&) = delete;

    virtual ~TimeWheelTimerTask() = default;

    // cancel task
    virtual bool cancel() = 0;
};

class TimeWheelTimer
{
public:
    TimeWheelTimer() = default;
    TimeWheelTimer(const TimeWheelTimer&) = delete;
    TimeWheelTimer(TimeWheelTimer&&) = delete;
    TimeWheelTimer& operator=(const TimeWheelTimer&) = delete;
    TimeWheelTimer&& operator=(TimeWheelTimer&&) = delete;

    virtual ~TimeWheelTimer() = default;

    // construct task
    virtual TimeWheelTimerTask::Ptr newTask(std::function<void()> _task, uint32_t _delayMS) = 0;
};

}  // namespace octopus