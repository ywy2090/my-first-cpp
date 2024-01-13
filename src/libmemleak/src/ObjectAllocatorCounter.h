#pragma once
#include <atomic>

namespace octopus
{
namespace memleak
{

template <typename T>
class ObjectAllocatorCounter
{
public:
    ObjectAllocatorCounter(const ObjectAllocatorCounter&) = delete;
    ObjectAllocatorCounter(ObjectAllocatorCounter&&) = delete;
    ObjectAllocatorCounter& operator=(const ObjectAllocatorCounter&) = delete;
    ObjectAllocatorCounter& operator=(ObjectAllocatorCounter&&) = delete;

    ObjectAllocatorCounter() { incrNewC(); }
    virtual ~ObjectAllocatorCounter() { incrFreeC(); }

    static void incrNewC() { ++m_newC; }
    static void incrFreeC() { ++m_freeC; }

    static uint64_t getNewC() { return m_newC; }
    static uint64_t getFreeC() { return m_freeC; }
    static uint64_t getAliveC() { return m_newC - m_freeC; }

private:
    static std::atomic<uint64_t> m_newC;
    static std::atomic<uint64_t> m_freeC;
};

template <typename T>
std::atomic<uint64_t> ObjectAllocatorCounter<T>::m_newC{0};
template <typename T>
std::atomic<uint64_t> ObjectAllocatorCounter<T>::m_freeC{0};

}  // namespace memleak
}  // namespace octopus