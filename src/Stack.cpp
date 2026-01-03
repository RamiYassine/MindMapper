#include <iostream>
#include "../include/Stack.h"

namespace Mapper {

// Default constructor
Stack::Stack() : m_top(nullptr), m_Title(1, '-'), m_Done(false)
{
}

// Constructor passed a title - set m_Title
Stack::Stack(const String& title) : m_top(nullptr), m_Title(title), m_Done(false)
{
}

// Copy Constructor
Stack::Stack(const Stack& other)
{
    Array<String> arr;
    Thought *tmp = other.getTop();
    while (tmp) {
        arr.append(tmp->phrase);
        tmp = tmp->next;
    }
    try {
        for (int i = arr.getLength() - 1; i >= 0; i--)
        {
            String phrase = arr.get(i);
            this->push(phrase);
        }
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    m_Title = other.getTitle();
    m_Done = other.isDone();
}

// Copy assignment operator
Stack& Stack::operator=(const Stack& other) {
    if (this == &other)
        return *this; // self-assignment check

    Thought* tmp;
    // Release current resources
    while (m_top) {
        tmp = m_top;
        m_top = m_top->next;
        delete tmp;
    }
    m_top = nullptr;

    Array<String> arr;
    tmp = other.getTop();
    while (tmp) {
        arr.append(tmp->phrase);
        tmp = tmp->next;
    }
    try {
        for (int i = arr.getLength() - 1; i >= 0; i--)
        {
            String phrase = arr.get(i);
            this->push(phrase);
        }
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    m_Title = other.getTitle();
    m_Done = other.isDone();

    return *this;
}

Stack::~Stack()
{
    while (m_top) {
        Thought *tmp = m_top;
        m_top = m_top->next;
        delete tmp;
    }
}

// Add new thought
void Stack::push(const String& t)
{
    Thought *tmp = new Thought(t);
    if (tmp == NULL) {
        std::cout << "Stack is full" << std::endl;
    } else {
        tmp->next = m_top;
        m_top = tmp;
    }
}

// Pop last thought
void Stack::pop()
{
    if (m_top == nullptr) {
        std::cout << "Stack is empty!" << std::endl;
    } else {
        Thought *tmp = m_top;
        m_top = m_top->next;
        delete tmp;
    }
}

// Returns pointer to top of Stack
Thought* Stack::getTop() const
{
    return m_top;
}

// Return idea title
String Stack::getTitle() const
{
    return m_Title;
}

// Set idea title
void Stack::setTitle(const String& title)
{
    m_Title = title;
}

// Return status of idea
bool Stack::isDone() const
{
    return m_Done;
}

// Set status of idea
void Stack::setStatus(const bool stat)
{
    m_Done = stat;
}

// Display thoughts in idea
void Stack::display(const Thought* p) const
{
    if (!p)
        return;
    display(p->next);
    std::cout << "- " << p->phrase.c_str() << std::endl;
}

} // namespace Mapper
