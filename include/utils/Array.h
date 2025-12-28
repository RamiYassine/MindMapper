#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <iostream>

namespace Mapper
{
template <typename T>
class Array final
{
public:
    Array();
    Array(size_t sz);
    Array(size_t sz, T val);
    Array(const Array& other);
    ~Array();

    void append(T val);
    void insert(T val, size_t ndx);
    T get(size_t ndx);
    void display();

    size_t getLength() const;
    T* data() const;
private:
    T* m_Data;
    size_t m_Size;
    size_t m_Length;
};

template <typename T>
Array<T>::Array()
{
    size_t sz = 15;
    m_Data = new T[sz];
    m_Size = sz;
    m_Length = 0;
}

template <typename T>
Array<T>::Array(size_t sz) : m_Data(new T[sz]), m_Size(sz), m_Length(0)
{
}

template <typename T>
Array<T>::Array(size_t sz, T val) : m_Data(new T[sz]), m_Size(sz), m_Length(0)
{
    for (size_t i = 0; i < sz; i++) {
        m_Data[i] = val;
        m_Length++;
    }
}

template <typename T>
Array<T>::Array(const Array& other) : m_Data(new T[other.getLength()]), m_Size(other.getLength()), m_Length(other.getLength())
{
    T* data = other.data();
    std::copy(data, data+other.getLength(), m_Data);
}

template <typename T>
Array<T>::~Array()
{
    if (m_Data) {
        delete []m_Data;
        m_Data = nullptr;
    }
}

template <typename T>
void Array<T>::append(T val)
{
    if (m_Length < m_Size) {
        m_Data[m_Length++] = val;
    } else {
        size_t newSize = m_Size * 2;
        T *tmp = new T[newSize];
        for (size_t i = 0; i < m_Length; i++)
            tmp[i] = m_Data[i];
        delete [] m_Data;
        m_Data = tmp;
        m_Size = newSize;
        m_Data[m_Length++] = val;
    }
}

template <typename T>
void Array<T>::insert(T val, size_t ndx)
{
    if (ndx >= 0 && ndx <= m_Length) {
        if (m_Length < m_Size) {
            for (size_t i = m_Length; i > ndx; i--)
                m_Data[i] = m_Data[i-1];
            m_Data[ndx] = val;
            m_Length++;
        } else {
            size_t newSize = m_Size * 2;
            T *tmp = new T[newSize];
            for (size_t i = 0; i < m_Length; i++)
                tmp[i] = m_Data[i];
            delete [] m_Data;
            m_Data = tmp;
            m_Size = newSize;
            for (size_t i = m_Length; i > ndx; i--)
                m_Data[i] = m_Data[i-1];
            m_Data[ndx] = val;
            m_Length++;
        }
    }
}

// return item at index if index is valid
// otherwise return -1
template <typename T>
T Array<T>::get(size_t ndx)
{
    if (ndx >= 0 && ndx < m_Length)
        return m_Data[ndx];
    throw std::out_of_range("Array index out of range");
}

template <typename T>
void Array<T>::display()
{
    for (size_t i = 0; i < m_Length; i++) {
        std::cout << m_Data[i];
    }
    std::cout << endl;
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
