#pragma once
#include <exception>
#include <functional>
#include <memory>

namespace octopus::executor
{

// TODO: impl more executor
class Executor
{
public:
    using Ptr = std::shared_ptr<Executor>;
    Executor() = default;
    Executor(const Executor&) = delete;
    Executor(Executor&&) = delete;
    Executor& operator=(const Executor&) = delete;
    Executor&& operator=(Executor&&) = delete;

    virtual ~Executor() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void run(std::function<void()> _task) noexcept = 0;
};

class DefaultExecutor : public Executor
{
public:
    DefaultExecutor() = default;
    DefaultExecutor(const DefaultExecutor&) = delete;
    DefaultExecutor(DefaultExecutor&&) = delete;
    DefaultExecutor& operator=(const DefaultExecutor&) = delete;
    DefaultExecutor&& operator=(DefaultExecutor&&) = delete;

    ~DefaultExecutor() override = default;

    void start() override {}
    void stop() override {}

    void run(std::function<void()> _task) noexcept override
    {
        try
        {
            _task();
        }
        catch (std::exception& _e)
        {
            // TODO:
        }
    }
};

}  // namespace octopus::executor