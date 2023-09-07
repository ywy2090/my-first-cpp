#include "MyMath.h"
#include <benchmark/benchmark.h>

// https://github.com/google/benchmark/blob/main/docs/user_guide.md
static void DoSetup(const benchmark::State& state) {}

static void DoTeardown(const benchmark::State& state) {}


static void BM_MyMath_add(benchmark::State& state)
{
    math::Math math;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(math.add(1, 2));
    }
}

static void BM_MyMath_sub(benchmark::State& state)
{
    math::Math math;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(math.sub(1, 2));
    }
}

// Register the function as a benchmark
BENCHMARK(BM_MyMath_add)
    ->Arg(1)
    ->Arg(3)
    ->Threads(16)
    ->Threads(32)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown);

BENCHMARK(BM_MyMath_sub)
    ->Arg(1)
    ->Arg(3)
    ->Threads(16)
    ->Threads(32)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown);

BENCHMARK_MAIN();