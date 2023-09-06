#include <benchmark/benchmark.h>


// https://github.com/google/benchmark/blob/main/docs/user_guide.md
static void DoSetup(const benchmark::State& state) 
{

}

static void DoTeardown(const benchmark::State& state) 
{
}


static void BM_StringCreation(benchmark::State& state)
{
    for (auto _ : state)
        std::string empty_string;
}

// Register the function as a benchmark
BENCHMARK(BM_StringCreation)->Arg(1)->Arg(3)->Threads(16)->Threads(32)->Setup(DoSetup)->Teardown(DoTeardown);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state)
{
    std::string x = "hello";
    for (auto _ : state)
        std::string copy(x);
}
BENCHMARK(BM_StringCopy)->Arg(1)->Arg(3)->Threads(16)->Threads(32)->Setup(DoSetup)->Teardown(DoTeardown);



BENCHMARK_MAIN();