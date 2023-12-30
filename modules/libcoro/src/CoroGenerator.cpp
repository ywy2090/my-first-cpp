#include <coroutine>
#include <iostream>
#include <optional>

// https://en.cppreference.com/w/cpp/language/coroutines

template <std::movable T>
class Generator
{
public:
    struct my_suspend_always
    {
        constexpr bool await_ready() const noexcept
        {
            std::cout << " => [suspend_always] await_ready " << std::endl;
            return false;
        }

        constexpr void await_suspend(std::coroutine_handle<>) const noexcept
        {
            std::cout << " => [suspend_always] await_suspend " << std::endl;
        }

        constexpr void await_resume() const noexcept
        {
            std::cout << " => [suspend_always] await_resume " << std::endl;
        }
    };

    struct my_suspend_never
    {
        constexpr bool await_ready() const noexcept
        {
            std::cout << " => [suspend_never] await_ready " << std::endl;
            return true;
        }

        constexpr void await_suspend(std::coroutine_handle<>) const noexcept
        {
            std::cout << " => [suspend_never] await_suspend " << std::endl;
        }

        constexpr void await_resume() const noexcept
        {
            std::cout << " => [suspend_never] await_resume " << std::endl;
        }
    };

public:
    struct promise_type
    {
        Generator<T> get_return_object()
        {
            std::cout << " => [promise_type] get_return_object " << std::endl;
            return Generator{Handle::from_promise(*this)};
        }

        static my_suspend_always initial_suspend() noexcept
        {
            std::cout << " => [promise_type] initial_suspend " << std::endl;
            return {};
        }

        static my_suspend_always final_suspend() noexcept
        {
            std::cout << " => [promise_type] final_suspend " << std::endl;
            return {};
        }

        my_suspend_always yield_value(T value) noexcept
        {
            std::cout << " => [promise_type] yield_value " << std::endl;
            current_value = std::move(value);
            return {};
        }

        // Disallow co_await in generator coroutines.
        void await_transform() = delete;
        [[noreturn]] static void unhandled_exception()
        {
            std::cout << " => [promise_type] unhandled_exception " << std::endl;
            throw;
        }

        std::optional<T> current_value;
    };

    using Handle = std::coroutine_handle<promise_type>;

    explicit Generator(const Handle coroutine) : m_coroutine{coroutine} {}

    Generator() = default;
    ~Generator()
    {
        if (m_coroutine)
        {
            m_coroutine.destroy();
        }
    }

    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    Generator(Generator&& other) noexcept : m_coroutine{other.m_coroutine}
    {
        other.m_coroutine = {};
    }
    Generator& operator=(Generator&& other) noexcept
    {
        if (this != &other)
        {
            if (m_coroutine)
            {
                m_coroutine.destroy();
            }
            m_coroutine = other.m_coroutine;
            other.m_coroutine = {};
        }
        return *this;
    }

    // Range-based for loop support.
    class Iter
    {
    public:
        void operator++()
        {
            std::cout << " => [Iter] ++  call coroutine.resume()" << std::endl;
            m_coroutine.resume();
        }
        const T& operator*() const
        {
            std::cout << " => [Iter] * " << std::endl;
            return *m_coroutine.promise().current_value;
        }
        bool operator==(std::default_sentinel_t) const
        {
            return !m_coroutine || m_coroutine.done();
        }

        explicit Iter(const Handle coroutine) : m_coroutine{coroutine} {}

    private:
        Handle m_coroutine;
    };

    Iter begin()
    {
        std::cout << " => [Iter] begin() call coroutine.resume()" << std::endl;
        if (m_coroutine)
        {
            m_coroutine.resume();
        }
        return Iter{m_coroutine};
    }

    std::default_sentinel_t end()
    {
        std::cout << " => [Iter] end() " << std::endl;
        return {};
    }

private:
    Handle m_coroutine;
};

template <std::integral T>
Generator<T> range(T first, const T last)
{
    std::cout << " => [range] in " << std::endl;
    while (first < last)
    {
        co_yield first;
        std::cout << " => [range] while loop "
                  << " first : " << first << std::endl;
        first++;
    }

    std::cout << " => [range] out " << std::endl;
}

int main()
{
    std::cout << " => [main] in " << std::endl;
    // for (const auto& i : range(65, 91))
    for (const auto& i : range(65, 70))
    {
        std::cout << " => [main] char: " << (char)i << ' ' << std::endl;
    }

    std::cout << " => [main] out " << std::endl;
}