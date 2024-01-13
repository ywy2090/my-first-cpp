#include "libtimewheel/src/HashedWheelTimerList.h"
#include "libtimewheel/src/HashedTimeWheelTimerTask.h"

#include <gtest/gtest.h>

// https://google.github.io/googletest/

using namespace octopus;
using namespace octopus::timewheel;

TEST(HashedWheelTimerListTest, AddAssertions)
{
    // create list
    auto list = std::make_shared<HashedWheelTimerList>();

    {
        // first task
        auto task = std::make_shared<HashedTimeWheelTimerTask>([]() { return; }, 1000);
        // first node
        auto listNode = std::make_shared<HashedWheelTimerNode>();
        listNode->task = std::move(task);

        list->appendNode(listNode);
        ASSERT_EQ(list->head, listNode);
        ASSERT_EQ(list->tail, listNode);
        ASSERT_EQ(list->listNodeC, 1);

        {
            auto newC = HashedTimeWheelTimerTask::getNewC();
            auto freeC = HashedTimeWheelTimerTask::getFreeC();

            ASSERT_EQ(newC, 1);
            ASSERT_EQ(freeC, 0);
        }

        {
            auto newC = HashedWheelTimerNode::getNewC();
            auto freeC = HashedWheelTimerNode::getFreeC();

            ASSERT_EQ(newC, 1);
            ASSERT_EQ(freeC, 0);
        }

        list->eraseNode(listNode);

        // release node and task
        listNode.reset();

        {
            auto newC = HashedTimeWheelTimerTask::getNewC();
            auto freeC = HashedTimeWheelTimerTask::getFreeC();

            ASSERT_EQ(newC, 1);
            ASSERT_EQ(freeC, 1);
            ASSERT_EQ(list->listNodeC, 0);
        }

        {
            auto newC = HashedWheelTimerNode::getNewC();
            auto freeC = HashedWheelTimerNode::getFreeC();

            ASSERT_EQ(newC, 1);
            ASSERT_EQ(freeC, 1);
        }
    }
}