#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include "Array.h"

namespace Mapper {

class String final
{
public:
    String(); // Default constructor - creates empty string
    String(size_t sz, char ch); // Construct a string with (char) repeated (size) times
    String(const Array<char>& arr); // Construct a string from a copy of this array
    String(const char* str); // Construct a string from C-Style string
    String(const String& other); // Copy constructor
    String& operator=(const String& other); // Copy assignment operator
    ~String() = default;

    void append(char ch); // Add a char to the end of the string
    const char* c_str() const; // Returns a pointer to a null-terminated char array
    size_t getLength() const; // Returns length of internal char array
    Array<char>* getString() const; // Returns pointer to the internal char array
private:
    std::unique_ptr<Array<char>> m_String;
};

} // namespace Mapper
#endif // STRING_H
