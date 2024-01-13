#pragma once
#include "HashedTimeWheelTimerTask.h"
#include <cassert>

namespace octopus::timewheel
{
class HashedTimeWheelTimerTask;

struct HashedWheelTimerNode : public memleak::ObjectAllocatorCounter<HashedWheelTimerNode>
{
    using Ptr = std::shared_ptr<HashedWheelTimerNode>;
    HashedWheelTimerNode::Ptr next{nullptr};
    HashedWheelTimerNode::Ptr prev{nullptr};

    // std::shared_ptr<HashedTimeWheelTimerTask> task;
    HashedTimeWheelTimerTask::Ptr task;
};

struct HashedWheelTimerList : public memleak::ObjectAllocatorCounter<HashedWheelTimerList>
{
    using Ptr = std::shared_ptr<HashedWheelTimerList>;
    // head node
    HashedWheelTimerNode::Ptr head{nullptr};
    // tail node
    HashedWheelTimerNode::Ptr tail{nullptr};

    // create node
    static HashedWheelTimerNode::Ptr createNode(HashedTimeWheelTimerTask::Ptr _task)
    {
        auto nodePtr = std::make_shared<HashedWheelTimerNode>();
        nodePtr->task = std::move(_task);
        return nodePtr;
    }

    // create node
    void createNodeAndAppendNode(HashedTimeWheelTimerTask::Ptr _task)
    {
        auto node = createNode(std::move(_task));
        appendNode(node);
    }

    // append node to list tail
    void appendNode(HashedWheelTimerNode::Ptr _node);
    // remove node
    void eraseNode(HashedWheelTimerNode::Ptr _node);


    // list node count
    int listNodeC{0};
};
}  // namespace octopus::timewheel