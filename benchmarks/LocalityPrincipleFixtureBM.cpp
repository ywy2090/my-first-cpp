#include <benchmark/benchmark.h>
#include <sys/types.h>
#include <cstddef>
#include <iterator>

// https://github.com/google/benchmark/blob/main/docs/user_guide.md

template <size_t M, size_t N>
class LocalityPrincipleFixture : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State& state) override {}
    void TearDown(const ::benchmark::State& state) override {}

    inline size_t getM() const { return M; }
    inline size_t getN() const { return N; }

public:
    int m_intArray[M][N] = {};
};


BENCHMARK_TEMPLATE_F(LocalityPrincipleFixture, BM_LocalityPrincipleTest, 10000, 10000)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        size_t m = getM();
        size_t n = getN();
        size_t r = 0;
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                r = m_intArray[i][j];
                benchmark::DoNotOptimize(r);
            }
        }
    }
}

BENCHMARK_TEMPLATE_F(LocalityPrincipleFixture, BM_NotLocalityPrincipleTest, 10000, 10000)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        size_t m = getM();
        size_t n = getN();
        size_t r = 0;
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                r = m_intArray[j][i];
                benchmark::DoNotOptimize(r);
            }
        }
    }
}
