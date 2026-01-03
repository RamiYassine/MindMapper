#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <iostream>

namespace Mapper {

template <typename T>
class Array;

template <typename T>
std::ostream& operator<<(std::ostream& o, const Array<T>& rhs);

template <typename T>
class Array final
{
public:
    Array();
    Array(size_t sz);
    Array(size_t sz, T val);
    Array(const Array& other);
    Array& operator=(const Array& other);
    // Array(Array&& other);
    // Array& operator=(Array&& other);
    ~Array();

    void append(const T& val);
    void insert(const T& val, size_t ndx);
    T get(size_t ndx) const;
    T& operator[](size_t ndx) const;
    void display() const;

    friend std::ostream& operator<< <>(std::ostream& o, const Array<T>& rhs);

    size_t getLength() const;
    T* data() const;
private:
    size_t m_Size;
    size_t m_Length;
    T* m_Data;

    void resize();
};

// create an empty array of size 10
template <typename T>
Array<T>::Array()
    : m_Size(10), m_Length(0), m_Data(new T[m_Size])
{
}

// create an array of a size equal to the parameter passed
template <typename T>
Array<T>::Array(size_t sz)
    : m_Size(sz), m_Length(0), m_Data(new T[m_Size])
{
}

// create an array of sz size and initialize all values to val
template <typename T>
Array<T>::Array(size_t sz, T val)
    : m_Size(sz), m_Length(0), m_Data(new T[m_Size])
{
    for (size_t i = 0; i < sz; i++) {
        m_Data[i] = val;
        m_Length++;
    }
}

// Copy constructor
template <typename T>
Array<T>::Array(const Array& other)
    : m_Size(other.getLength()),
    m_Length(other.getLength()),
    m_Data(new T[other.getLength()])
{
    std::copy(other.data(), other.data()+m_Length, m_Data);
}

// Copy assignment operator
template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this == &other) // check for self-assignment
        return *this;

    if (m_Data)
        delete [] m_Data;

    m_Size = other.m_Size;
    m_Length = other.m_Length;
    m_Data = new T[m_Size];
    std::copy(other.data(), other.data()+m_Length, m_Data);

    return *this;
}

// // Move constructor
// template <typename T>
// Array<T>::Array(Array&& other)
// {

// }

// // move assignment operator
// template <typename T>
// Array<T>& Array<T>::operator=(Array&& other)
// {

// }

template <typename T>
Array<T>::~Array()
{
    if (m_Data) {
        delete [] m_Data;
        m_Data = nullptr;
    }
}

// grow the array when needed by doubling its size
template <typename T>
void Array<T>::resize()
{
    size_t newSize = m_Size * 2;
    T *tmp = new T[newSize];
    if (tmp) {
        for (size_t i = 0; i < m_Length; i++)
            tmp[i] = m_Data[i];
        delete[] m_Data;
        m_Data = tmp;
        m_Size = newSize;
    } else {
        throw std::bad_alloc();
    }
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
    return m_Data;
}

} // namespace Mapper
#endif // ARRAY_H
