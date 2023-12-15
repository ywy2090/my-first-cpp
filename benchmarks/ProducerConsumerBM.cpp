#include <benchmark/benchmark.h>
#include <concurrentqueue/moodycamel/concurrentqueue.h>
#include <sys/types.h>
#include <list>
#include <mutex>
#include <queue>
#include <vector>

// https://github.com/google/benchmark/blob/main/docs/user_guide.md

class ProducerConsumerFixture : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State& state) override {}

    void TearDown(const ::benchmark::State& state) override {}

    // for moodycamel::ConcurrentQueue
    inline void runConcurrentQueue(benchmark::State& state, int threadIndex)
    {
        if ((threadIndex % 2) != 0)
        {
            // enqueue
            m_concurrentQueue.enqueue(1);
        }
        else
        {
            // dequeue
            int out{0};
            bool result = m_concurrentQueue.try_dequeue(out);
            benchmark::DoNotOptimize(out);
            benchmark::DoNotOptimize(result);
        }
    }

    // for mutex queue
    inline void runMutexQueue(benchmark::State& state, int threadIndex)
    {
        if ((threadIndex % 2) != 0)
        {
            // enqueue
            std::lock_guard<std::mutex> lock(x_queue);
            m_queue.push(1);
        }
        else
        {
            // dequeue
            std::lock_guard<std::mutex> lock(x_queue);
            if (!m_queue.empty())
            {
                m_queue.pop();
            }
        }
    }

protected:
    // moodycamel::ConcurrentQueue
    moodycamel::ConcurrentQueue<int> m_concurrentQueue;

    // queue
    std::queue<int> m_queue;
    std::mutex x_queue;

    // list
    std::list<int> m_list;
    std::mutex x_list;

    // vector
    std::vector<int> m_vector;
    std::mutex x_vector;
};


BENCHMARK_DEFINE_F(ProducerConsumerFixture, concurrentQueueTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        int threadIndex = state.thread_index();
        if ((threadIndex % 2) != 0)
        {
            // enqueue
            m_concurrentQueue.enqueue(1);
        }
        else
        {
            // dequeue
            int out{0};
            bool result = m_concurrentQueue.try_dequeue(out);
            benchmark::DoNotOptimize(out);
            benchmark::DoNotOptimize(result);
        }
    }
}

BENCHMARK_DEFINE_F(ProducerConsumerFixture, mutexQueueTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        int threadIndex = state.thread_index();
        if ((threadIndex % 2) != 0)
        {
            // enqueue
            std::lock_guard<std::mutex> lock(x_queue);
            m_queue.push(1);
        }
        else
        {
            // dequeue
            std::lock_guard<std::mutex> lock(x_queue);
            if (!m_queue.empty())
            {
                int r = m_queue.back();
                m_queue.pop();
                benchmark::DoNotOptimize(r);
            }
        }
    }
}


BENCHMARK_DEFINE_F(ProducerConsumerFixture, mutexListTest)(benchmark::State& state)
{
    for (auto _ : state)
    {
        int threadIndex = state.thread_index();
        if ((threadIndex % 2) != 0)
        {
            // enqueue
            std::lock_guard<std::mutex> lock(x_list);
            m_list.push_back(1);
        }
        else
        {
            // dequeue
            std::lock_guard<std::mutex> lock(x_list);
            if (!m_list.empty())
            {
                int r = m_list.back();
                m_list.pop_back();
                benchmark::DoNotOptimize(r);
            }
        }
    }
}

/* enqueueTest is NOT registered */
BENCHMARK_REGISTER_F(ProducerConsumerFixture, concurrentQueueTest)->ThreadRange(2, 64);
BENCHMARK_REGISTER_F(ProducerConsumerFixture, mutexQueueTest)->ThreadRange(2, 64);
BENCHMARK_REGISTER_F(ProducerConsumerFixture, mutexListTest)->ThreadRange(2, 64);

// BENCHMARK_MAIN();