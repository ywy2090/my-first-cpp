
#include "HashedWheelTimerList.h"

using namespace octopus;
using namespace octopus::timewheel;

// append node to list tail
void HashedWheelTimerList::appendNode(HashedWheelTimerNode::Ptr _node)
{
    listNodeC++;
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
void HashedWheelTimerList::eraseNode(HashedWheelTimerNode::Ptr _node)
{
    if (!_node)
    {
        return;
    }

    listNodeC--;
    auto& prevNode = _node->prev;
    auto& nextNode = _node->next;

    // single node
    if (!prevNode && !nextNode)
    {
        head = tail = nullptr;
    }
    // node is head
    else if (!prevNode)
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
