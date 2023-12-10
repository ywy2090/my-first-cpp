#include <benchmark/benchmark.h>
#include <sys/types.h>
#include <cstddef>
#include <iterator>

// https://github.com/google/benchmark/blob/main/docs/user_guide.md

template <size_t M, size_t N>
class LocalityPrincipleFixture : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State& state) override
    {
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                intArray[i][j] = i * 10 + j;
            }
        }
    }

    inline size_t getM() const { return M; }
    inline size_t getN() const { return N; }

    void TearDown(const ::benchmark::State& state) override {}

protected:
    int intArray[M][N] = {};
};


BENCHMARK_TEMPLATE_F(LocalityPrincipleFixture, lpTest, 10000, 10000)(benchmark::State& state)
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
                benchmark::DoNotOptimize(r = intArray[i][j]);
            }
        }
    }
}

BENCHMARK_TEMPLATE_F(LocalityPrincipleFixture, notLpTest, 10000, 10000)(benchmark::State& state)
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
                benchmark::DoNotOptimize(r = intArray[j][i]);
            }
        }
    }
}

// BENCHMARK_REGISTER_F(LocalityPrincipleFixture, lpTest)->Name("LocalityPrinciple");
// BENCHMARK_REGISTER_F(LocalityPrincipleFixture, notLpTest)->Name("NotLocalityPrinciple");
