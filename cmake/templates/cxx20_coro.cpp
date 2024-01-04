#include <coroutine>
#include <iostream>
#include <string_view>

struct HelloCoroutine {
    struct HelloPromise {
        std::string_view value_;

        HelloCoroutine get_return_object() {
            return std::coroutine_handle<HelloPromise>::from_promise(*this);
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() { return {}; }
        void unhandled_exception() {}

        std::suspend_always yield_value(std::string_view value) {
            value_ = value;
            std::cout << value_ << std::endl;
            return {};
        }
    };

    using promise_type = HelloPromise;
    HelloCoroutine(std::coroutine_handle<HelloPromise> h) : handle(h) {}

    std::coroutine_handle<HelloPromise> handle;
};

HelloCoroutine hello() {
    std::string_view s = "Hello ";
    co_yield s;

    std::cout << "world" << std::endl;
}

int main() {
    HelloCoroutine coro = hello();

    std::cout << "calling resume" << std::endl;
    coro.handle.resume();

    std::cout << "destroy" << std::endl;
    coro.handle.destroy();

    return 0;
}