#pragma once
#include "HashedTimeWheelTimerTask.h"
#include <cassert>
#include <memory>

namespace octopus
{

class HashedTimeWheelTimerTask;

struct HashedWheelTimerNode
{
    using Ptr = std::shared_ptr<HashedWheelTimerNode>;
    HashedWheelTimerNode::Ptr next{nullptr};
    HashedWheelTimerNode::Ptr prev{nullptr};

    std::shared_ptr<HashedTimeWheelTimerTask> task;
};

struct HashedWheelTimerList
{
    using Ptr = std::shared_ptr<HashedWheelTimerList>;
    // head node
    HashedWheelTimerNode::Ptr head{nullptr};
    // tail node
    HashedWheelTimerNode::Ptr tail{nullptr};

    // create node
    static HashedWheelTimerNode::Ptr createNode(std::shared_ptr<HashedTimeWheelTimerTask> _task)
    {
        auto nodePtr = std::make_shared<HashedWheelTimerNode>();
        nodePtr->task = std::move(_task);
        return nodePtr;
    }

    // create node
    void createNodeAndAppendNode(std::shared_ptr<HashedTimeWheelTimerTask> _task)
    {
        auto node = createNode(std::move(_task));
        appendNode(node);
    }

    // append node to list tail
    void appendNode(HashedWheelTimerNode::Ptr& _node)
    {
        // list is empty
        if (!head && !tail)
        {
            head = tail = _node;
            return;
        }

        // list is not empty, append node to list tail
        auto& newTailNode = _node;
        auto& oldTailNode = tail;
        assert(oldTailNode);
        oldTailNode->next = newTailNode;
        newTailNode->prev = oldTailNode;
        oldTailNode = newTailNode;
    }

    // remove list node
    void eraseNode(HashedWheelTimerNode::Ptr& _node)
    {
        if (!_node)
        {
            return;
        }

        auto& prevNode = _node->prev;
        auto& nextNode = _node->next;

        // node is head
        if (!prevNode)
        {
            head = nextNode;
            if (head)
            {
                head->prev = nullptr;
            }
        }
        // node is tail
        else if (!nextNode)
        {
            tail = prevNode;
            if (tail)
            {
                tail->next = nullptr;
            }
        }
        // node is middle
        else
        {
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
        }
    }
};

}  // namespace octopus