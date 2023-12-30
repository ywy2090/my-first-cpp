#include <coroutine>

#include <asyncio/callstack.h>
#include <asyncio/exception.h>
#include <asyncio/gather.h>
#include <asyncio/runner.h>
#include <asyncio/sleep.h>
#include <asyncio/task.h>

using namespace std::literals::chrono_literals;


asyncio::Task<int> factorial(int n)
{
    if (n <= 1)
    {
        co_await asyncio::dump_callstack();
        co_return 1;
    }
    co_return (co_await factorial(n - 1)) * n;
}

int main()
{
    fmt::print("run result: {}\n", asyncio::run(factorial(10)));
    return 0;
}


/*
asyncio::Task<> hello_world()
{
    fmt::print("hello\n");
    co_await asyncio::sleep(1s);
    fmt::print("world\n");
}

int main()
{
    asyncio::run(hello_world());
}
*/