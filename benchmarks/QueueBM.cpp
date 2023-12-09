#include <benchmark/benchmark.h>
#include <concurrentqueue/moodycamel/concurrentqueue.h>
#include <sys/types.h>
#include <cstddef>
#include <iterator>

// https://github.com/google/benchmark/blob/main/docs/user_guide.md

class QueueFixture : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State& state) override {}

    void TearDown(const ::benchmark::State& state) override {}

protected:
    moodycamel::ConcurrentQueue<int> q;
};


BENCHMARK_DEFINE_F(QueueFixture, enqueueTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        q.enqueue(1);
    }
}
/* enqueueTest is NOT registered */
BENCHMARK_REGISTER_F(QueueFixture, enqueueTest)->Threads(16);
// BENCHMARK_REGISTER_F(QueueFixture, enqueueTest);

// BENCHMARK_REGISTER_F(QueueFixture, lpTest)->Name("Queue");
// BENCHMARK_REGISTER_F(QueueFixture, notLpTest)->Name("NotQueue");


// BENCHMARK_MAIN();