#include <benchmark/benchmark.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>

// https://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array
// !!! TODO: impossible to reproduce with -03 optimization level

template <std::size_t N>
class BranchPredicationFixtureBM : public benchmark::Fixture
{
public:
    BranchPredicationFixtureBM()
    {
        std::cout << "getN() : " << getN() << std::endl;
        // init array data
        for (std::size_t i = 0; i < getN(); ++i)
        {
            int r = std::rand() % 256;
            m_outOfOrderData[i] = r;
            m_sortedData[i] = r;
        }

        // sort m_sortedData
        std::sort(m_sortedData, m_sortedData + N);
    }

    inline std::size_t getN() const { return N; }

    void SetUp(const ::benchmark::State& state) override {}

    void TearDown(const ::benchmark::State& state) override {}

protected:
    int m_outOfOrderData[N] = {};
    int m_sortedData[N] = {};
};


BENCHMARK_TEMPLATE_DEFINE_F(BranchPredicationFixtureBM, BM_BranchPredicationTest_sortedArray, 32768)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        long long sum = 0;
        unsigned n = getN();
        for (unsigned i = 0; i < 100000; ++i)
        {
            for (std::size_t j = 0; j < n; ++j)
            {  // Primary loop.
                if (m_sortedData[j] >= 128)
                {
                    sum += m_sortedData[j];
                }
            }
        }
        benchmark::DoNotOptimize(sum);
    }
}


BENCHMARK_TEMPLATE_DEFINE_F(
    BranchPredicationFixtureBM, BM_BranchPredicationTest_outOfOrderArray, 32768)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        long long sum = 0;
        unsigned n = getN();
        for (unsigned i = 0; i < 100000; ++i)
        {
            for (std::size_t j = 0; j < n; ++j)
            {  // Primary loop.
                if (m_outOfOrderData[j] >= 128)
                {
                    sum += m_outOfOrderData[j];
                }
            }
        }
        benchmark::DoNotOptimize(sum);
    }
}


BENCHMARK_TEMPLATE_DEFINE_F(
    BranchPredicationFixtureBM, BM_BranchPredicationTest_sortedArray_bitOp, 32768)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        long long sum = 0;
        unsigned n = getN();
        for (unsigned i = 0; i < 100000; ++i)
        {
            for (std::size_t j = 0; j < n; ++j)
            {  // Primary loop.
                int t = (m_sortedData[j] - 128) >> 31;
                sum += ~t & m_sortedData[j];
            }
        }
        benchmark::DoNotOptimize(sum);
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(
    BranchPredicationFixtureBM, BM_BranchPredicationTest_outOfOrderArray_bitOp, 32768)
(benchmark::State& state)
{
    for (auto _ : state)
    {
        long long sum = 0;
        unsigned n = getN();
        for (unsigned i = 0; i < 100000; ++i)
        {
            for (std::size_t j = 0; j < n; ++j)
            {  // Primary loop.
                int t = (m_outOfOrderData[j] - 128) >> 31;
                sum += ~t & m_outOfOrderData[j];
            }
        }
        benchmark::DoNotOptimize(sum);
    }
}

BENCHMARK_REGISTER_F(BranchPredicationFixtureBM, BM_BranchPredicationTest_sortedArray);
BENCHMARK_REGISTER_F(BranchPredicationFixtureBM, BM_BranchPredicationTest_outOfOrderArray);
BENCHMARK_REGISTER_F(BranchPredicationFixtureBM, BM_BranchPredicationTest_sortedArray_bitOp);
BENCHMARK_REGISTER_F(BranchPredicationFixtureBM, BM_BranchPredicationTest_outOfOrderArray_bitOp);
