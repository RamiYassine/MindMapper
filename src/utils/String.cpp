#include "../../include/utils/String.h"

String::String()
{
    m_String = new Array<char>();
    m_String->append('\0');
}

String::String(size_t sz, char ch)
{
    m_String = new Array<char>(sz, ch);
    m_String->append('\0');
}

String::String(Array<char>& str) : m_String(&str)
{
    if (m_String->get(m_String->getLength() - 1) != '\0')
        m_String->append('\0');
}

String::String(const String& other) : m_String(new Array<char>(*(other.getString())))
{
}

String& String::operator=(const String& other)
{
    delete m_String;
    m_String = new Array<char>(*(other.getString()));
    return *this;
}

String::~String()
{
    delete m_String;
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
    return m_String;
}
