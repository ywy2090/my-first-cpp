#pragma once
#include <atomic>

namespace octopus
{
namespace objref
{

template <typename T>
class ObjectRefCount
{
public:
    ObjectRefCount(const ObjectRefCount&) = delete;
    ObjectRefCount(ObjectRefCount&&) = delete;
    ObjectRefCount& operator=(const ObjectRefCount&) = delete;
    ObjectRefCount& operator=(ObjectRefCount&&) = delete;

    ObjectRefCount() { incrNewC(); }
    virtual ~ObjectRefCount() { incrFreeC(); }

    static void incrNewC() { ++m_newC; }
    static void incrFreeC() { ++m_freeC; }

    static uint64_t getNewC() { return m_newC; }
    static uint64_t getFreeC() { return m_freeC; }

private:
    static std::atomic<uint64_t> m_newC;
    static std::atomic<uint64_t> m_freeC;
};

template <typename T>
std::atomic<uint64_t> ObjectRefCount<T>::m_newC{0};
template <typename T>
std::atomic<uint64_t> ObjectRefCount<T>::m_freeC{0};

}  // namespace objref
}  // namespace octopus