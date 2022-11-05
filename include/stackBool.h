#include <climits>

namespace containers
{
    template <>
    class Stack<bool> {
    public:
        Stack();
        Stack(size_t mx_size);
        Stack(const Stack &stack);
        Stack(Stack &&stack);
        ~Stack();

        void push(const uint8_t &val);
        void pop();
        void resize (size_t);

        Stack &operator=(const Stack &);
        Stack &operator=(Stack &&);

        int isFull() const;
        int isEmpty() const;
        size_t get_size() const;
        size_t get_mx_size() const;
        uint8_t get_top() const;
        static size_t bits_to_bytes(size_t);

    private:
        uint8_t *data_;
        size_t mx_size_;
        size_t size_;
    };
}  // namespace containers

size_t containers::Stack<bool>::bits_to_bytes(size_t mx_size)
{
    size_t bytes = mx_size / BITS_IN_BYTE;

    if (mx_size % BITS_IN_BYTE == 0)
        return bytes;

    else
        return bytes + 1;
}

containers::Stack<bool>::Stack()
{
    data_ = nullptr;
    mx_size_ = 0;
    size_ = 0;
}

containers::Stack<bool>::Stack(size_t mx_size)
{
    mx_size_ = containers::Stack<bool>::bits_to_bytes(mx_size) * CHAR_BIT;
    size_ = 0;

    size_t size_in_bytes = bits_to_bytes(mx_size);
    data_ = new uint8_t[size_in_bytes];

    for (size_t i = 0; i < size_in_bytes; ++i)
        data_[i] = 0;
}

containers::Stack<bool>::Stack(const Stack &stack)
{
    data_ = new uint8_t[stack.mx_size_];
    size_ = stack.size_;

    for (size_t i = 0; i < stack.size_; ++i)
        data_[i] = stack.data_[i];
}

containers::Stack<bool>::Stack(Stack &&stack)
{
    data_ = stack.data_;
    size_ = stack.size_;
    mx_size_ = stack.mx_size_;
    stack.data_ = nullptr;
}

containers::Stack<bool>::~Stack()
{
    delete[] data_;
}

containers::Stack<bool> &containers::Stack<bool>::operator=(const Stack &stack)
{
    if (this == &stack)
        return *this;

    mx_size_ = stack.mx_size_;
    size_ = stack.size_;

    size_t size_in_bytes = bits_to_bytes(size_);
    for (size_t i = 0; i < size_in_bytes; ++i)
        data_[i] = stack.data_[i];

    return *this;
}

containers::Stack<bool> &containers::Stack<bool>::operator=(Stack &&stack)
{
    data_ = stack.data_;
    mx_size_ = stack.mx_size_;
    size_ = stack.size_;

    stack.data_ = nullptr;
    return *this;
}

size_t containers::Stack<bool>::get_size() const
{
    return this->size_;
}

size_t containers::Stack<bool>::get_mx_size() const
{
    return this->mx_size_;
}

uint8_t containers::Stack<bool>::get_top() const
{
    size_t val = containers::Stack<bool>::bits_to_bytes(size_);
    std::cout << "val = " << val << "\n";
    std::cout << "I return " << data_[1] << "\n";
    return data_[1];
}

int containers::Stack<bool>::isFull() const
{
    std::cout << "size_ = " << size_ << std::endl;
    std::cout << "counter size = " << containers::Stack<bool>::bits_to_bytes(mx_size_) * 8 << std::endl;
    return (size_ == containers::Stack<bool>::bits_to_bytes(mx_size_) * CHAR_BIT) ? true : false;
}

int containers::Stack<bool>::isEmpty() const
{
    return (this->size_ == 0) ? true : false;
}

void containers::Stack<bool>::push(const uint8_t &val)
{
    if (this->isFull()) {
        size_t newSize = static_cast<size_t> (containers::EXP_COEFF * mx_size_);
        this->resize (newSize);
    }

    size_++;

    int byte_num = containers::Stack<bool>::bits_to_bytes(size_) - 1;
    int curr_pos = (size_ - 1) % containers::BITS_IN_BYTE;

    if (val == 1) {
        uint8_t val = 1;
        val = val << (containers::BITS_IN_BYTE - curr_pos - 1);
        data_[byte_num] += val;
    }
}

void containers::Stack<bool>::pop()
{
    if (!this->isEmpty ())
        --size_;
}

void containers::Stack<bool>::resize (size_t newSize)
{
    std::cout << "New size " << newSize <<std::endl;
    std::cout << "old size " << size_ <<std::endl;
    size_t oldSizeInBytes = containers::Stack<bool>::bits_to_bytes(size_);
    size_t newSizeInBytes = containers::Stack<bool>::bits_to_bytes(newSize);
    std::cout <<"New size in bytes " << newSizeInBytes <<std::endl;
    uint8_t* newData = new uint8_t[newSizeInBytes];
    std::copy (data_, data_ + oldSizeInBytes - 1, newData);
    delete [] data_;
    data_ = newData;
    std::cout << "sfsgssg" << newData[0] << std::endl;
    mx_size_ = newSizeInBytes * CHAR_BIT;
}