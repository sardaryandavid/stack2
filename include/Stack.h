#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace containers {
static const int BITS_IN_BYTE = 8;
static const double EXP_COEFF = 1.5;
template <typename T>
class Stack {
public:
    Stack();
    Stack(size_t mx_size);
    Stack(const Stack &stack);
    Stack(Stack &&stack);
    ~Stack();

    void push(const T &val);
    void pop();
    void resize(size_t);

    Stack &operator=(const Stack &);
    Stack &operator=(Stack &&);

    int isFull() const;
    int isEmpty() const;
    size_t get_size() const;
    size_t get_mx_size() const;
    T get_top() const;

private:
    T *data_;
    size_t capacity;
    size_t size_;
};
}  // namespace containers

template <typename T>
containers::Stack<T>::Stack()
{
    data_ = nullptr;
    capacity = 0;
    size_ = 0;
}

template <typename T>
containers::Stack<T>::Stack(size_t mx_size)
{
    capacity = mx_size;
    size_ = 0;
    data_ = new T[mx_size];
}

template <typename T>
containers::Stack<T>::Stack(const Stack &stack)
{
    data_ = new T[stack.mx_size];
    size_ = stack.size_;
    capacity = stack.capacity;

    for (int i = 0; i < stack.size_; ++i)
        data_[i] = stack.data_[i];
}

template <typename T>
containers::Stack<T>::Stack(Stack &&stack)
{
    data_ = stack.data_;
    size_ = stack.size_;
    capacity = stack.capacity;
    stack.data_ = nullptr;
}

template <typename T>
containers::Stack<T>::~Stack()
{
    delete[] data_;
}

template <typename T>
containers::Stack<T> &containers::Stack<T>::operator=(const Stack &stack)
{
    if (this == &stack)
        return *this;

    capacity = stack.capacity;
    size_ = stack.size_;

    for (size_t i = 0; i < size_; ++i)
        data_[i] = stack.data_[i];

    return *this;
}

template <typename T>
containers::Stack<T> &containers::Stack<T>::operator=(Stack &&stack)
{
    data_ = stack.data_;
    capacity = stack.capacity;
    size_ = stack.size_;

    stack.data_ = nullptr;
    return *this;
}

template <typename T>
size_t containers::Stack<T>::get_size() const
{
    return this->size_;
}

template <typename T>
size_t containers::Stack<T>::get_mx_size() const
{
    return this->capacity;
}

template <typename T>
T containers::Stack<T>::get_top() const
{
    return this->data_[size_ - 1];
}

template <typename T>
int containers::Stack<T>::isFull() const
{
    return (this->size_ == this->capacity) ? true : false;
}

template <typename T>
int containers::Stack<T>::isEmpty() const
{
    return (this->size_ == 0) ? true : false;
}

template <typename T>
void containers::Stack<T>::push(const T &val)
{
    if (this->isFull()) {
        size_t newSize = static_cast<size_t>(containers::EXP_COEFF * capacity);
        this->resize(newSize);
    }

    data_[size_++] = val;
}

template <typename T>
void containers::Stack<T>::pop()
{
    if (!this->isEmpty()) {
        --size_;
    }
}

template <typename T>
void containers::Stack<T>::resize(size_t newSize)
{
    T *newData = new T[newSize];
    std::copy(data_, data_ + capacity, newData);
    delete[] data_;
    data_ = newData;

    for (size_t i = size_; i < capacity; ++i)
        data_[i] = 0;

    capacity = newSize;
}

#endif