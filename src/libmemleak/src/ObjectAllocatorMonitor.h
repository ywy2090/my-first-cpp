#pragma once
#include <atomic>
#include <iostream>

namespace octopus
{
namespace memleak
{

// template class declaration
template <typename... ARGS>
struct ObjectAllocStatToString
{
};

// template class specialization
template <>
struct ObjectAllocStatToString<>
{
    static std::string toString(const std::string& _delimiter = " ") { return ""; }
};

template <typename TYPE, typename... ARGS>
struct ObjectAllocStatToString<TYPE, ARGS...> : public ObjectAllocStatToString<ARGS...>
{
    static std::string toString(const std::string& _delimiter = " ")
    {
        auto newObjC = TYPE::getNewC();
        auto freeObjC = TYPE::getFreeC();
        auto aliveObjC = TYPE::getAliveC();

        return std::string("[ type: ") + typeid(TYPE).name() +
               " ,created: " + std::to_string(newObjC) +
               " ,destroyed: " + std::to_string(freeObjC) +
               " ,alive: " + std::to_string(aliveObjC) + " ]" + _delimiter +
               ObjectAllocStatToString<ARGS...>::toString(_delimiter);
    }
};

class ObjectAllocatorMonitor
{
public:
    ObjectAllocatorMonitor(const ObjectAllocatorMonitor&) = delete;
    ObjectAllocatorMonitor(ObjectAllocatorMonitor&&) = delete;
    ObjectAllocatorMonitor& operator=(const ObjectAllocatorMonitor&) = delete;
    ObjectAllocatorMonitor& operator=(ObjectAllocatorMonitor&&) = delete;

    ObjectAllocatorMonitor() = default;
    ~ObjectAllocatorMonitor() = default;

    template <typename... ARGS>
    std::string monitorObj()
    {
        return ObjectAllocStatToString<ARGS...>::toString();
    }
};

}  // namespace memleak
}  // namespace octopus