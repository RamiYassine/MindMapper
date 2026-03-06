#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <memory>

namespace Mapper {

template <typename T>
class Array;

template <typename T>
std::ostream& operator<<(std::ostream& o, const Array<T>& rhs);

// class to replace std::vector for this project
template <typename T>
class Array final
{
private:
    size_t m_Size; // array size
    size_t m_Length; // used size
    std::unique_ptr<T[]> m_Data; // ptr to array data

    void resize(); // function to resize the array

public:
    Array(); // default constructor
    Array(size_t sz); // construct with specific size
    Array(size_t sz, T val); // construct with specific size and set data to val
    template <typename U = T,
                typename = std::enable_if_t<std::is_same_v<U, char>>>
    Array(const char* str); // specialized consturctor
    Array(const Array& other); // copy constructor
    Array& operator=(const Array& other); // copy assingment
    Array(Array&& other) noexcept; // move constructor
    Array& operator=(Array&& other) noexcept; // move assignment
    ~Array() = default; // destructor

    void append(const T& val);
    void insert(const T& val, size_t ndx);
    T get(size_t ndx) const;
    T& operator[](size_t ndx) const;
    void display() const;

    friend std::ostream& operator<< <>(std::ostream& o, const Array<T>& rhs);

    size_t getLength() const;
    T* data() const;
};

template <typename T>
Array<T>::Array()
    : m_Size(10), m_Length(0), m_Data(std::make_unique<T[]>(m_Size))
{
}

template <typename T>
Array<T>::Array(size_t sz)
    : m_Size(sz), m_Length(0), m_Data(std::make_unique<T[]>(m_Size))
{
}

template <typename T>
Array<T>::Array(size_t sz, T val)
    : m_Size(sz), m_Length(0), m_Data(std::make_unique<T[]>(m_Size))
{
    for (size_t i = 0; i < sz; i++) {
        m_Data[i] = val;
        m_Length++;
    }
}

template <typename T>
template <typename U, typename>
Array<T>::Array(const char* str)
    : m_Size(std::strlen(str) + 1),
    m_Length(m_Size),
    m_Data(std::make_unique<T[]>(m_Size))
{
    std::copy(str, str+m_Size, m_Data.get());
}

template <typename T>
Array<T>::Array(const Array& other)
    : m_Size(other.getLength()),
    m_Length(other.getLength()),
    m_Data(std::make_unique<T[]>(other.getLength()))
{
    std::copy(other.data(), other.data() + m_Length, m_Data.get());
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this == &other) // check for self-assignment
        return *this;

    m_Size = other.m_Size;
    m_Length = other.m_Length;
    m_Data = std::make_unique<T[]>(m_Size);
    std::copy(other.data(), other.data() + m_Length, m_Data.get());

    return *this;
}

template <typename T>
Array<T>::Array(Array&& other) noexcept
    : m_Size(other.m_Size),
    m_Length(other.m_Length),
    m_Data(std::move(other.m_Data))
{
    other.m_Size = 0;
    other.m_Length = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept
{
    if (this == &other) return *this;
    m_Size = other.m_Size;
    m_Length = other.m_Length;
    m_Data = std::move(other.m_Data);

    other.m_Size = 0;
    other.m_Length = 0;

    return *this;
}

// grow the array when needed by doubling its size
template <typename T>
void Array<T>::resize()
{
    size_t newSize = m_Size * 2;
    auto newData = std::make_unique<T[]>(newSize);

    for (size_t i = 0; i < m_Length; i++)
        newData[i] = std::move(m_Data[i]);

    m_Data = std::move(newData);
    m_Size = newSize;
}

// append new value to end of array
template <typename T>
void Array<T>::append(const T& val)
{
    if (m_Length >= m_Size)
        resize();
    m_Data[m_Length++] = val;
}

// insert new value at index ndx
template <typename T>
void Array<T>::insert(const T& val, size_t ndx)
{
    if (ndx <= m_Length) {
        if (m_Length >= m_Size)
            resize();

        for (size_t i = m_Length; i > ndx; i--)
            m_Data[i] = m_Data[i-1];
        m_Data[ndx] = val;
        m_Length++;
    } else {
        throw std::out_of_range("Bad index for insertion");
    }
}

// return item at index if index is valid
template <typename T>
T Array<T>::get(size_t ndx) const
{
    if (ndx >= 0 && ndx < m_Length)
        return m_Data[ndx];
    throw std::out_of_range("Index requested is out of range");
}

template <typename T>
T& Array<T>::operator[](size_t ndx) const
{
    if (ndx >= 0 && ndx < m_Length)
        return m_Data[ndx];
    throw std::out_of_range("Index requested is out of range");
}

template <typename T>
void Array<T>::display() const
{
    for (size_t i = 0; i < m_Length; i++)
        std::cout << m_Data[i];
    std::cout << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const Array<T>& rhs)
{
    for (size_t i = 0; i < rhs.m_Length; i++)
        o << rhs.m_Data[i];
    o << std::endl;
    return o;
}

template <typename T>
size_t Array<T>::getLength() const
{
    return m_Length;
}

template <typename T>
T* Array<T>::data() const
{
    return m_Data.get();
}

} // namespace Mapper
#endif // ARRAY_H
