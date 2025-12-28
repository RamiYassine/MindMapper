#ifndef STACK_H
#define STACK_H

#include "utils/String.h"

namespace Mapper
{
class Thought final
{
public:
    String phrase;
    Thought *next;

    Thought(const String& str) {
        phrase = str;
        next = nullptr;
    }
};

class Stack final
{
public:
    Stack();
    Stack(const String& title);
    Stack(const Stack &stk);
    Stack& operator=(const Stack& stk);
    ~Stack();

    void push(const String &t);
    void pop();
    Thought* getTop() const;
    String getTitle() const;
    void setTitle(const String& title);
    bool isDone() const;
    void setStatus(const bool stat);
    void display(Thought* p);
private:
    Thought *m_top;
    String m_Title;
    bool m_Done;
};
} // namespace Mapper

#endif // STACK_H
