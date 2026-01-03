#include "../../include/utils/String.h"

namespace Mapper {

// Default constructor - creates empty string
String::String() : m_String(new Array<char>())
{
    m_String->append('\0');
}

// Constructor with size and char - creates a string with (char) repeated (size) times
String::String(size_t sz, char ch) : m_String(new Array<char>(sz, ch))
{
    m_String->append('\0');
}

// Constructor with reference to an already existing array - creates a string from a copy of this array
String::String(const Array<char>& arr) : m_String(new Array<char>(arr))
{
    try {
        if (m_String->get(m_String->getLength() - 1) != '\0')
            m_String->append('\0');
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}

// Copy constructor
String::String(const String& other) : m_String(new Array<char>(*(other.getString())))
{
}

// Copy assignment operator
String& String::operator=(const String& other)
{
    if (this == &other)
        return *this;

    if (m_String)
        delete m_String;

    m_String = new Array<char>(*(other.getString()));
    return *this;
}

String::~String()
{
    delete m_String;
}

// Add a char to the end of the string
void String::append(char ch)
{
    m_String->insert(ch, m_String->getLength() - 1);
}

// Returns a pointer to an array that contains a null-terminated sequence of characters
const char* String::c_str() const
{
    return m_String->data();
}

// Returns length of internal Array<char>
size_t String::getLength() const
{
    return m_String->getLength();
}

// Returns pointer to Array<char>
Array<char>* String::getString() const
{
    return m_String;
}

} // namespace Mapper
