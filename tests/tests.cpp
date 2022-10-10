#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Stack.h"

using namespace containers;

TEST(get_size, test) 
{
    int val = 5;
    const size_t mx_size = 10;
    Stack<int> stack {mx_size};
    stack.push(val);

    ASSERT_TRUE(stack.get_size () == 1);
}

TEST(get_mx_size, test) 
{
    const size_t mx_size = 10;
    Stack<int> stack {mx_size};

    ASSERT_TRUE(stack.get_mx_size () == mx_size);
}

TEST(push, test) 
{
    int val = 5;
    const int mx_size = 10;
    Stack<int> stack {mx_size};
    
    for (int i = 0; i < mx_size; ++i)
        stack.push (val + i);

    for (int i = 0; i < mx_size; ++i)
        ASSERT_TRUE(stack.get_pdata()[i] == val + i);
}

TEST(pop, test) 
{
    int val = 5;
    const size_t mx_size = 10;
    Stack<int> stack {mx_size};
    stack.push (val);
    stack.pop ();

    ASSERT_TRUE(stack.get_size () == 0);
}

TEST(isFull, test) 
{
    int val = 5;
    const size_t mx_size = 10;
    Stack<int> stack {mx_size};
    
    for (size_t i = 0; i < mx_size; ++i)
        stack.push (val + i);
    
    ASSERT_TRUE(stack.isFull () == 1);
}

TEST(isEmpty, test) 
{
    const size_t mx_size = 10;
    Stack<int> stack {mx_size};
    
    ASSERT_TRUE(stack.isEmpty () == 1);
}

TEST(operator_assign, test)
{
    int val = 5;
    const size_t mx_size = 10;
    Stack<int> stack1 {mx_size};
    Stack<int> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push (val + i);    
    
    stack2 = stack1;

    ASSERT_TRUE(stack1.get_mx_size () == stack2.get_mx_size () &&
                stack1.get_size    () == stack2.get_size    ());
    
    for (size_t i = 0; i < mx_size; ++i)
        ASSERT_TRUE(stack1.get_pdata()[i] == stack1.get_pdata()[i]);
}

TEST(move_operator_assign, test) 
{
    int val = 5;
    const size_t mx_size = 10;
    Stack<int> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack2.push (val + i);    
    
    Stack<int> stack1 = std::move(stack2);

    ASSERT_TRUE(stack1.get_mx_size () == stack2.get_mx_size () &&
                stack1.get_size    () == stack2.get_size    ());
    
    for (size_t i = 0; i < mx_size; ++i)
        ASSERT_TRUE(stack1.get_pdata()[i] == stack1.get_pdata()[i]);
}

/**************************************/

TEST(get_size_bool, test) 
{
    int val = 5;
    const size_t mx_size = 10;
    Stack<bool> stack {mx_size};
    stack.push(val);

    ASSERT_TRUE(stack.get_size () == 1);
}

TEST(get_mx_size_bool, test) 
{
    const size_t mx_size = 10;
    Stack<bool> stack {mx_size};

    ASSERT_TRUE(stack.get_mx_size () == mx_size);
}

TEST(push_bool, test) 
{
    int val = 1;
    const int mx_size = 10;
    Stack<bool> stack {mx_size};
    
    for (int i = 0; i < mx_size; ++i)
        stack.push (val);

    ASSERT_TRUE(stack.get_pdata()[0] == 255);
    ASSERT_TRUE(stack.get_pdata()[1] == 192);
}

TEST(pop_bool, test) 
{
    int val = 5;
    const size_t mx_size = 10;
    Stack<bool> stack {mx_size};
    stack.push (val);
    stack.pop ();

    ASSERT_TRUE(stack.get_size () == 0);
}

TEST(isFull_bool, test) 
{
    int val = 1;
    const size_t mx_size = 10;
    Stack<bool> stack {mx_size};
    
    for (size_t i = 0; i < mx_size; ++i)
        stack.push (val);
    
    ASSERT_TRUE(stack.isFull () == 1);
}

TEST(isEmpty_bool, test) 
{
    const size_t mx_size = 10;
    Stack<bool> stack {mx_size};
    
    ASSERT_TRUE(stack.isEmpty () == 1);
}

TEST(operator_assign_bool, test)
{
    int val = 1;
    const size_t mx_size = 10;
    Stack<bool> stack1 {mx_size};
    Stack<bool> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack1.push (val);    
    
    stack2 = stack1;

    ASSERT_TRUE(stack1.get_mx_size () == stack2.get_mx_size () &&
                stack1.get_size    () == stack2.get_size    ());
    
    for (size_t i = 0; i < containers::bits_to_bytes (mx_size); ++i)
        ASSERT_TRUE(stack1.get_pdata()[i] == stack1.get_pdata()[i]);
}

TEST(move_operator_assign_bool, test) 
{
    int val = 1;
    const size_t mx_size = 10;
    Stack<bool> stack2 {mx_size};

    for (size_t i = 0; i < mx_size; ++i)
        stack2.push (val);    
    
    Stack<bool> stack1 = std::move(stack2);

    ASSERT_TRUE(stack1.get_mx_size () == stack2.get_mx_size () &&
                stack1.get_size    () == stack2.get_size    ());
    
    for (size_t i = 0; i < containers::bits_to_bytes (mx_size); ++i)
        ASSERT_TRUE(stack1.get_pdata()[i] == stack1.get_pdata()[i]);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
  
    return RUN_ALL_TESTS();
}