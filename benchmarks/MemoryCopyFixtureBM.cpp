#include <benchmark/benchmark.h>
#include <array>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <iterator>

// https://github.com/google/benchmark/blob/main/docs/user_guide.md


template <std::size_t N>
class MemoryCopyFixture : public benchmark::Fixture
{
public:
    MemoryCopyFixture()
    {
        m_src.fill('0');
        m_dst.fill('0');
    }


    void SetUp(const ::benchmark::State& state) override {}

    void TearDown(const ::benchmark::State& state) override {}

protected:
    std::array<char, N> m_src;
    std::array<char, N> m_dst;
};


BENCHMARK_TEMPLATE_DEFINE_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_1k, 1024)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        memcpy(m_dst.data(), m_src.data(), m_src.size());
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * m_src.size());
}

BENCHMARK_TEMPLATE_DEFINE_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_10k, 10240)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        memcpy(m_dst.data(), m_src.data(), m_src.size());
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * m_src.size());
}

BENCHMARK_TEMPLATE_DEFINE_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_20k, 20480)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        memcpy(m_dst.data(), m_src.data(), m_src.size());
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * m_src.size());
}

BENCHMARK_TEMPLATE_DEFINE_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_30k, 30720)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        memcpy(m_dst.data(), m_src.data(), m_src.size());
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * m_src.size());
}

BENCHMARK_TEMPLATE_DEFINE_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_100k, 102400)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        memcpy(m_dst.data(), m_src.data(), m_src.size());
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * m_src.size());
}

BENCHMARK_REGISTER_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_1k);
BENCHMARK_REGISTER_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_10k);
BENCHMARK_REGISTER_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_20k);
BENCHMARK_REGISTER_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_30k);
BENCHMARK_REGISTER_F(MemoryCopyFixture, BM_MemoryCopyFixtureTest_100k);