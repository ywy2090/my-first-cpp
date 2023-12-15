
#include <benchmark/benchmark.h>
#include <atomic>
#include <cstdint>
#include <mutex>

class AtomicIntFixture : public benchmark::Fixture
{
public:
    void SetUp(const ::benchmark::State& state) override
    {
        // printf("SetUp ==> %d\n", m_atomicValue.is_lock_free());
    }

    void TearDown(const ::benchmark::State& state) override {}

protected:
    std::atomic<int64_t> m_atomicValue{0};

    int64_t m_intValue{0};
    std::mutex x_mutex;
};

BENCHMARK_DEFINE_F(AtomicIntFixture, BM_AtomicIncrTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        m_atomicValue++;
    }
}

BENCHMARK_DEFINE_F(AtomicIntFixture, BM_MutexIncrTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::lock_guard<std::mutex> lock(x_mutex);
        m_intValue++;
    }
}

BENCHMARK_REGISTER_F(AtomicIntFixture, BM_AtomicIncrTest)->ThreadRange(1, 32);
BENCHMARK_REGISTER_F(AtomicIntFixture, BM_MutexIncrTest)->ThreadRange(1, 32);
