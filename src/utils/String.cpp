#include "../../include/utils/String.h"

namespace Mapper {

String::String() : m_String(std::make_unique<Array<char>>())
{
    m_String->append('\0');
}

String::String(size_t sz, char ch) : m_String(std::make_unique<Array<char>>(sz, ch))
{
    m_String->append('\0');
}

String::String(const Array<char>& arr) : m_String(std::make_unique<Array<char>>(arr))
{
    try {
        if (m_String->get(m_String->getLength() - 1) != '\0')
            m_String->append('\0');
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}

String::String(const char* str) : m_String(std::make_unique<Array<char>>(str))
{
    try {
        if (m_String->get(m_String->getLength() - 1) != '\0')
            m_String->append('\0');
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}

String::String(const String& other) : m_String(std::make_unique<Array<char>>(*(other.getString())))
{
}

String& String::operator=(const String& other)
{
    if (this == &other)
        return *this;

    m_String = std::make_unique<Array<char>>(*(other.getString()));
    return *this;
}

void String::append(char ch)
{
    m_String->insert(ch, m_String->getLength() - 1);
}

const char* String::c_str() const
{
    return m_String->data();
}

size_t String::getLength() const
{
    return m_String->getLength();
}

Array<char>* String::getString() const
{
    return m_String.get();
}

} // namespace Mapper
