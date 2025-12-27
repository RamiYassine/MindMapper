#include <iostream>
#include "../include/Stack.h"

using namespace std;

Stack::Stack() : m_top(nullptr), m_Title(1, '-'), m_Done(false)
{
}

Stack::Stack(const String& title) : m_top(nullptr), m_Title(title), m_Done(false)
{
}

Stack::Stack(const Stack &stk)
{
    this->m_Title = stk.getTitle();
    this->m_Done = stk.isDone();
    Array<String> arr;
    Thought *tmp = stk.getTop();
    while (tmp) {
        arr.append(tmp->phrase);
        tmp = tmp->next;
    }
    for (int i = arr.getLength() - 1; i >= 0; i--)
    {
        String phrase = arr.get(i);
        this->push(phrase);
    }
}

Stack& Stack::operator=(const Stack& stk) {
    if (this == &stk)
        return *this; // self-assignment check

    Thought* tmp;
    // Release current resources
    while (m_top) {
        tmp = m_top;
        m_top = m_top->next;
        delete tmp;
    }
    m_top = nullptr;

    this->m_Title = stk.getTitle();
    this->m_Done = stk.isDone();
    Array<String> arr;
    tmp = stk.getTop();
    while (tmp) {
        arr.append(tmp->phrase);
        tmp = tmp->next;
    }
    for (int i = arr.getLength() - 1; i >= 0; i--)
    {
        String phrase = arr.get(i);
        this->push(phrase);
    }

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

void Stack::push(const String &t)
{
    Thought *tmp = new Thought(t);
    if (tmp == NULL) {
        cout << "Stack is full" << endl;
    } else {
        tmp->next = m_top;
        m_top = tmp;
    }
}

void Stack::pop()
{
    if (m_top == nullptr) {
        cout << "Stack is empty!" << endl;
    } else {
        Thought *tmp = m_top;
        m_top = m_top->next;
        delete tmp;
    }
}

Thought* Stack::getTop() const
{
    return m_top;
}

String Stack::getTitle() const
{
    return m_Title;
}

void Stack::setTitle(const String& title)
{
    m_Title = title;
}

bool Stack::isDone() const
{
    return m_Done;
}

void Stack::setStatus(const bool stat)
{
    m_Done = stat;
}

void Stack::display(Thought* p)
{
    if (!p) {
        return;
    }
    display(p->next);
    cout << "- " << p->phrase.c_str() << endl;
}
