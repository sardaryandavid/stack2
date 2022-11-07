#include "Stack.h"
#include "stackBool.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <climits>

TEST(stackTest, get_size)
{
    size_t val = 5;
    const size_t mx_size = 10;
    containers::Stack<int> stack {mx_size};
    stack.push(val);

    ASSERT_TRUE(stack.get_size() == 1);
}

TEST(stackTest, get_mx_size)
{
    const size_t mx_size = 10;
    containers::Stack<int> stack {mx_size};

    ASSERT_TRUE(stack.get_mx_size() == mx_size);
}

TEST(stackTest, push)
{
    int val = 5;
    const int mx_size = 10;
    containers::Stack<int> stack {mx_size};

    for (int i = 0; i < mx_size; ++i)
        stack.push(val + i);

    ASSERT_TRUE(stack.get_top() == static_cast<int>(val + stack.get_size() - 1));
}

TEST(stackTest, push_more_mxSize)
{
    int val = 5;
    const int mx_size = 10;
    containers::Stack<int> stack {mx_size};

    for (int i = 0; i < 2 * mx_size; ++i)
        stack.push(val + i);

    ASSERT_TRUE(stack.get_top() == static_cast<int>(val + stack.get_size() - 1));
    ASSERT_TRUE(stack.get_size() == 2 * mx_size);
}

TEST(stackTest, pop)
{
    size_t val = 5;
    const size_t mx_size = 10;
    containers::Stack<int> stack {mx_size};
    stack.push(val);
    stack.pop();

    ASSERT_TRUE(stack.get_size() == 0);
}

TEST(stackTest, isFull)
{
    size_t val = 5;
    const size_t mx_size = 10;
    containers::Stack<int> stack1 {mx_size};
    containers::Stack<int> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push(val + i);

    for (size_t i = 0; i < mx_size - 1; ++i)
        stack2.push(val + i);

    ASSERT_TRUE(stack1.isFull() == 1);
    ASSERT_TRUE(stack2.isFull() == 0);
}

TEST(stackTest, isEmpty)
{
    const size_t mx_size = 10;
    containers::Stack<int> stack {mx_size};

    ASSERT_TRUE(stack.isEmpty() == 1);
}

TEST(stackTest, operator_assign)
{
    size_t val = 5;
    const size_t mx_size = 10;
    containers::Stack<int> stack1 {mx_size};
    containers::Stack<int> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push(val + i);

    stack2 = stack1;

    ASSERT_TRUE(stack1.get_mx_size() == stack2.get_mx_size() && stack1.get_size() == stack2.get_size());
    ASSERT_TRUE(stack1.get_top ()== stack1.get_top ());
}

TEST(stackTest, move_operator_assign)
{
    size_t val = 5;
    const size_t mx_size = 10;
    containers::Stack<int> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack2.push(val + i);

    containers::Stack<int> stack1 = std::move(stack2);

    ASSERT_TRUE(stack1.get_mx_size() == stack2.get_mx_size() && stack1.get_size() == stack2.get_size());
    ASSERT_TRUE(stack1.get_top () == stack1.get_top ());
}

TEST(stackTest, big_data)
{
    int val = 5;
    const size_t mx_size = 1000000;
    containers::Stack<int> stack1 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push(val + i);

    ASSERT_TRUE(stack1.get_size() == mx_size);
    ASSERT_TRUE(stack1.get_top() == static_cast<int>(val + stack1.get_size() - 1));
}

/**************************************/

TEST(boolStackTest, get_size_bool)
{
    size_t val = 5;
    const size_t mx_size = 10;
    containers::Stack<bool> stack {mx_size};
    stack.push(val);

    ASSERT_TRUE(stack.get_size() == 1);
}

TEST(boolStackTest, get_mx_size_bool)
{
    const size_t mx_size = 10;
    containers::Stack<bool> stack {mx_size};

    ASSERT_TRUE(stack.get_mx_size() == containers::Stack<bool>::bits_to_bytes(mx_size) * CHAR_BIT);
}

TEST(boolStackTest, push_bool)
{
    size_t val = 1;
    const int mx_size = 10;
    containers::Stack<bool> stack {mx_size};

    for (int i = 0; i < mx_size; ++i)
        stack.push(val);

    ASSERT_TRUE(stack.get_top() == 192);
}

TEST(boolStackTest, pop_bool)
{
    size_t val = 5;
    const size_t mx_size = 10;
    containers::Stack<bool> stack {mx_size};
    stack.push(val);
    stack.pop();

    ASSERT_TRUE(stack.get_size() == 0);
}

TEST(boolStackTest, isFull_bool)
{
    size_t val = 1;
    const size_t mx_size = 10;
    containers::Stack<bool> stack1 {mx_size};
    containers::Stack<bool> stack2 {CHAR_BIT * mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push(val);

    for (size_t i = 0; i < CHAR_BIT * mx_size; ++i)
        stack2.push(val);

    ASSERT_TRUE(stack1.isFull() == 0);
    ASSERT_TRUE(stack2.isFull() == 1);
}

TEST(boolStackTest, isEmpty_bool)
{
    const size_t mx_size = 10;
    containers::Stack<bool> stack {mx_size};

    ASSERT_TRUE(stack.isEmpty() == 1);
}

TEST(boolStackTest, operator_assign_bool)
{
    size_t val = 1;
    const size_t mx_size = 10;
    containers::Stack<bool> stack1 {mx_size};
    containers::Stack<bool> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push(val);

    stack2 = stack1;

    ASSERT_TRUE(stack1.get_mx_size() == stack2.get_mx_size() && stack1.get_size() == stack2.get_size());
    ASSERT_TRUE(stack1.get_top() == stack2.get_top());
}

TEST(boolStackTest, move_operator_assign_bool)
{
    size_t val = 1;
    const size_t mx_size = 10;
    containers::Stack<bool> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack2.push(val);

    containers::Stack<bool> stack1 = std::move(stack2);

    ASSERT_TRUE(stack1.get_mx_size() == stack2.get_mx_size() && stack1.get_size() == stack2.get_size());
    ASSERT_TRUE(stack1.get_top () == stack1.get_top ());
}

TEST(boolStackTest, big_data)
{
    const size_t mx_size = 1000000;
    containers::Stack<bool> stack1 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push(1);

    ASSERT_TRUE(stack1.get_size() == mx_size);
    ASSERT_TRUE(stack1.get_top() == 255);
}

TEST(boolStackTest, push_more_mxSize)
{
    bool val = 1;
    const size_t mx_size = 10;
    containers::Stack<bool> stack {mx_size};

    for (size_t i = 0; i < 2 * mx_size; ++i)
        stack.push(val);

    ASSERT_EQ(stack.get_top(), 240);
    ASSERT_TRUE(stack.get_size() == 2 * mx_size);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}