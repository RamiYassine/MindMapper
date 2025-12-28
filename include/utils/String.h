#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include "Array.h"

namespace Mapper
{
class String final
{
public:
    String();
    String(size_t sz, char ch);
    String(Array<char>& str);
    String(const String& other);
    String& operator=(const String& other);
    ~String();

    void append(char ch);
    const char* c_str() const;
    size_t getLength() const;
    Array<char>* getString() const;
private:
    Array<char>* m_String;
};
} // namespace Mapper

#endif // STRING_H
