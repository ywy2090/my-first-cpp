#include <benchmark/benchmark.h>
#include <cstddef>
#include <iostream>
#include <iterator>

// https://github.com/google/benchmark/blob/main/docs/user_guide.md


class VecIterFixture : public benchmark::Fixture
{
public:
    VecIterFixture() { m_iterArray.resize(0xFF); }

public:
    void SetUp(const ::benchmark::State& state) override {}

    void TearDown(const ::benchmark::State& state) override {}

protected:
    std::vector<int> m_iterArray;
};

BENCHMARK_DEFINE_F(VecIterFixture, BM_IterateByIndexTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        const auto size = m_iterArray.size();
        for (std::size_t i = 0; i < size; ++i)
        {
            int r = m_iterArray[i];
            benchmark::DoNotOptimize(r);
        }
    }
}

BENCHMARK_DEFINE_F(VecIterFixture, BM_IterateByRangeTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (auto& i : m_iterArray)
        {
            int j = i;
            benchmark::DoNotOptimize(j);
        }
    }
}

BENCHMARK_DEFINE_F(VecIterFixture, BM_IterateByPointerTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        auto* pend = &m_iterArray.back() + 1;
        for (auto* p = &m_iterArray.front(); p != pend; ++p)
        {
            int j = *p;
            benchmark::DoNotOptimize(j);
        }
    }
}

BENCHMARK_REGISTER_F(VecIterFixture, BM_IterateByIndexTest);
BENCHMARK_REGISTER_F(VecIterFixture, BM_IterateByRangeTest);
BENCHMARK_REGISTER_F(VecIterFixture, BM_IterateByPointerTest);
