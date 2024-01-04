#pragma once
#include <atomic>
#include <iostream>

namespace octopus
{
namespace objref
{

class ObjectRefCountMonitor
{
public:
    ObjectRefCountMonitor(const ObjectRefCountMonitor&) = delete;
    ObjectRefCountMonitor(ObjectRefCountMonitor&&) = delete;
    ObjectRefCountMonitor& operator=(const ObjectRefCountMonitor&) = delete;
    ObjectRefCountMonitor& operator=(ObjectRefCountMonitor&&) = delete;

    ObjectRefCountMonitor() = default;
    ~ObjectRefCountMonitor() = default;

    template <typename... Args>
    void monitor()
    {
        if (sizeof...(Args) == 0)
        {
            // std::cout << "ObjectRefCountMonitor: no object to monitor" << std::endl;
            return;
        }

        // if (sizeof...(Args) == 1)
        // {
        //     std::cout << "ObjectRefCountMonitor, " << typeid(Args).name() << std::endl;
        //     return;
        // }
    }
};

}  // namespace objref
}  // namespace octopus