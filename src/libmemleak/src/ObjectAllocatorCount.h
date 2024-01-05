#pragma once
#include <atomic>

namespace octopus
{
namespace objref
{

template <typename T>
class ObjectAllocatorCount
{
public:
    ObjectAllocatorCount(const ObjectAllocatorCount&) = delete;
    ObjectAllocatorCount(ObjectAllocatorCount&&) = delete;
    ObjectAllocatorCount& operator=(const ObjectAllocatorCount&) = delete;
    ObjectAllocatorCount& operator=(ObjectAllocatorCount&&) = delete;

    ObjectAllocatorCount() { incrNewC(); }
    virtual ~ObjectAllocatorCount() { incrFreeC(); }

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
std::atomic<uint64_t> ObjectAllocatorCount<T>::m_newC{0};
template <typename T>
std::atomic<uint64_t> ObjectAllocatorCount<T>::m_freeC{0};

}  // namespace objref
}  // namespace octopus