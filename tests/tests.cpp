#include "Stack.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

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

    for (int i = 0; i < mx_size; ++i)
        ASSERT_TRUE(stack.get_elem(i) == val + i);
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
    containers::Stack<int> stack {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack.push(val + i);

    ASSERT_TRUE(stack.isFull() == 1);
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

    for (size_t i = 0; i < mx_size; ++i)
        ASSERT_TRUE(stack1.get_elem(i) == stack1.get_elem(i));
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

    for (size_t i = 0; i < mx_size; ++i)
        ASSERT_TRUE(stack1.get_elem(i) == stack1.get_elem(i));
}

TEST(stackTest, big_data)
{
    int val = 5;
    const size_t mx_size = 1000000;
    containers::Stack<int> stack1 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push(val + i);

    ASSERT_TRUE(stack1.get_size() == mx_size);
    for (size_t i = 0; i < mx_size; ++i)
        ASSERT_TRUE(stack1.get_elem(i) == static_cast<int>(val + i));
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

    ASSERT_TRUE(stack.get_mx_size() == mx_size);
}

TEST(boolStackTest, push_bool)
{
    size_t val = 1;
    const int mx_size = 10;
    containers::Stack<bool> stack {mx_size};

    for (int i = 0; i < mx_size; ++i)
        stack.push(val);

    ASSERT_TRUE(stack.get_elem(0) == 255);
    ASSERT_TRUE(stack.get_elem(1) == 192);
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
    containers::Stack<bool> stack {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack.push(val);

    ASSERT_TRUE(stack.isFull() == 1);
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

    for (size_t i = 0; i < containers::Stack<bool>::bits_to_bytes(mx_size); ++i)
        ASSERT_TRUE(stack1.get_elem(i) == stack2.get_elem(i));
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

    size_t bytes_in_stack = containers::Stack<bool>::bits_to_bytes(mx_size);
    for (size_t i = 0; i < bytes_in_stack; ++i)
        ASSERT_TRUE(stack1.get_elem(i) == stack1.get_elem(i));
}

TEST(boolStackTest, big_data)
{
    const size_t mx_size = 1000000;
    containers::Stack<bool> stack1 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push(1);

    ASSERT_TRUE(stack1.get_size() == mx_size);

    size_t bytes_in_stack = containers::Stack<bool>::bits_to_bytes(mx_size);
    for (size_t i = 0; i < bytes_in_stack; ++i)
        ASSERT_TRUE(stack1.get_elem(i) == 255);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}