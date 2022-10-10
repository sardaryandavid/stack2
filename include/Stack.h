#pragma once
#include <cstddef>
#include "Stack.h"
#include <iostream>

namespace containers 
{
    const int BITS_IN_BYTE = 8;

    template <typename T>
    class Stack
    {
        enum {NO = 0, YES};

    public:
        Stack ();
        Stack (size_t mx_size);
        Stack (const Stack& stack);
        Stack (Stack&& stack);
        ~Stack ();

        void push (const T& val);
        void pop ();
        
        Stack& operator= (const Stack&  );
        Stack& operator= (Stack&& );

        int isFull  () const;
        int isEmpty () const;
        size_t get_size () const;
        size_t get_mx_size () const;
        T* get_pdata () const;

    private:
        T* data_;
        size_t mx_size_;
        size_t size_;
    };

    template<>
    class Stack<bool>
    {
        enum {NO = 0, YES};

    public:
        Stack ();
        Stack (size_t mx_size);
        Stack (const Stack& stack);
        Stack (Stack&& stack);
        ~Stack ();

        void push (const unsigned char& val);
        void pop ();
        
        Stack& operator= (const Stack&  );
        Stack& operator= (Stack&& );

        int isFull  () const;
        int isEmpty () const;
        size_t get_size () const;
        size_t get_mx_size () const;
        unsigned char* get_pdata () const;

    private:
        unsigned char* data_;
        size_t mx_size_;
        size_t size_;
    };

    size_t bits_to_bytes (size_t );
}

template <typename T>
containers::Stack<T>::Stack ()
{
    data_ = nullptr;
    mx_size_ = 0;
    size_ = 0;
}

template <typename T>
containers::Stack<T>::Stack (size_t mx_size)
{
    mx_size_ = mx_size;
    size_ = 0;
    data_ = new T[mx_size];
}

template <typename T>
containers::Stack<T>::Stack (const Stack& stack)
{
    data_ = new T[stack.mx_size];
    size_ = stack.size_;

    for (int i = 0; i < stack.size_; ++i)
        data_[i] = stack.data_[i];
}

template <typename T>
containers::Stack<T>::Stack (Stack&& stack)
{
    data_ = stack.data_;    
    size_ = stack.size_;
    mx_size_ = stack.mx_size_;
    stack.data_ = nullptr;
}

template <typename T>
containers::Stack<T>::~Stack ()
{
    delete [] data_;
}

template <typename T>
containers::Stack<T>& containers::Stack<T>::operator= (const Stack&  stack)
{
    mx_size_ = stack.mx_size_;
    size_ = stack.size_;

    for (size_t i = 0; i < size_; ++i)
        data_[i] = stack.data_[i];
    
    return *this;
}

template <typename T>
containers::Stack<T>& containers::Stack<T>::operator= (Stack&& stack)
{
    data_ = stack.data_;
    mx_size_ = stack.mx_size_;
    size_ = stack.size_;

    stack.data_ = nullptr;
    return *this;
}

/*****************************************/

const int BITS_IN_BYTE = 8;

size_t containers::bits_to_bytes (size_t mx_size)
{   
    size_t bytes = mx_size / BITS_IN_BYTE;
    
    if (mx_size % BITS_IN_BYTE == 0)
        return bytes;
    
    else
        return bytes + 1;
}

containers::Stack<bool>::Stack ()
{
    data_ = nullptr;
    mx_size_ = 0;
    size_ = 0;
}

containers::Stack<bool>::Stack (size_t mx_size)
{
    mx_size_ = mx_size;
    size_ = 0;

    size_t size_in_bytes = bits_to_bytes (mx_size);
    data_ = new unsigned char[size_in_bytes];
}

containers::Stack<bool>::Stack (const Stack& stack)
{
    data_ = new unsigned char[stack.mx_size_];
    size_ = stack.size_;

    for (size_t i = 0; i < stack.size_; ++i)
        data_[i] = stack.data_[i];
}

containers::Stack<bool>::Stack (Stack&& stack)
{
    data_ = stack.data_;    
    size_ = stack.size_;
    mx_size_ = stack.mx_size_;
    stack.data_ = nullptr;
}

containers::Stack<bool>::~Stack ()
{
    delete [] data_;
}

containers::Stack<bool>& containers::Stack<bool>::operator= (const Stack&  stack)
{
    mx_size_ = stack.mx_size_;
    size_ = stack.size_;

    for (size_t i = 0; i < size_; ++i)
        data_[i] = stack.data_[i];
    
    return *this;
}

containers::Stack<bool>& containers::Stack<bool>::operator= (Stack&& stack)
{
    data_ = stack.data_;
    mx_size_ = stack.mx_size_;
    size_ = stack.size_;

    stack.data_ = nullptr;
    return *this;
}

/*****************************************/

template <typename T>
size_t containers::Stack<T>::get_size () const
{
    return this->size_;
}

template <typename T>
size_t containers::Stack<T>::get_mx_size () const
{
    return this->mx_size_;
}

template<typename T>
T* containers::Stack<T>::get_pdata () const
{
    return this->data_;
}

template<typename T>
int containers::Stack<T>::isFull  () const
{
    return (this->size_ == this->mx_size_) ? YES : NO;
}
    
template<typename T>
int containers::Stack<T>::isEmpty () const
{
    return (this->size_ == 0) ? YES : NO;
}

size_t containers::Stack<bool>::get_size () const
{
    return this->size_;
}

size_t containers::Stack<bool>::get_mx_size () const
{
    return this->mx_size_;
}

unsigned char* containers::Stack<bool>::get_pdata () const
{
    return this->data_;
}

int containers::Stack<bool>::isFull  () const
{
    return (this->size_ == this->mx_size_) ? YES : NO;
}
    
int containers::Stack<bool>::isEmpty () const
{
    return (this->size_ == 0) ? YES : NO;
}

/*****************************************/

template<typename T>
void containers::Stack<T>::push (const T& val)
{
    if (this->isFull ()) 
    {
        std::cout << "Stack is full" << std::endl;
        exit (EXIT_FAILURE);
    }


    data_[size_++] = val;
}

template<typename T>
void containers::Stack<T>::pop ()
{
    if (this->isEmpty ()) 
    {
        std::cout << "Stack is empty" << std::endl;
        exit (EXIT_FAILURE);
    }

    --size_;
}

void containers::Stack<bool>::push (const unsigned char& val)
{
    if (this->isFull ()) 
    {
        std::cout << "Stack is full" << std::endl;
        exit (EXIT_FAILURE);
    }

    size_++;

    int byte_num = containers::bits_to_bytes (size_) - 1;
    int curr_pos = (size_ -1) % containers::BITS_IN_BYTE;

    if (val == 1)
        data_[byte_num] += (1 << (containers::BITS_IN_BYTE - curr_pos - 1));
}

void containers::Stack<bool>::pop ()
{
    if (this->isEmpty ()) 
    {
        std::cout << "Stack is empty" << std::endl;
        exit (EXIT_FAILURE);
    }

    --size_;
}