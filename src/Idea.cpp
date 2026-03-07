#include <iostream>
#include "../include/Idea.h"

namespace Mapper {

Idea::Idea() : m_top(nullptr), m_Title(1, '-'), m_Done(false)
{
}

Idea::Idea(const String& title) : m_top(nullptr), m_Title(title), m_Done(false)
{
}

Idea::Idea(const Idea& other)
{
    Array<String> arr;
    auto thought = other.getTop();
    while (thought) {
        arr.append(thought->phrase);
        thought = thought->next;
    }
    try {
        for (int i = arr.getLength() - 1; i >= 0; i--)
        {
            String phrase = arr.get(i);
            push(phrase);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    m_Title = other.getTitle();
    m_Done = other.isDone();
}

Idea& Idea::operator=(const Idea& other) {
    if (this == &other)
        return *this; // self-assignment check

    Array<String> arr;
    auto lastThought = other.getTop();
    while (lastThought) {
        arr.append(lastThought->phrase);
        lastThought = lastThought->next;
    }
    m_top.reset(); // release any current thoughts
    try {
        for (int i = arr.getLength() - 1; i >= 0; i--)
        {
            String phrase = arr.get(i);
            push(phrase);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    m_Title = other.getTitle();
    m_Done = other.isDone();

    return *this;
}

void Idea::push(const String& s)
{
    auto thought = std::make_shared<ThoughtNode>(s);
    if (!thought)
        throw std::runtime_error("Idea is full");
    thought->next = m_top;
    m_top = thought;
}

void Idea::pop()
{
    if (m_top == nullptr)
        throw std::runtime_error("Idea is empty!");
    auto tmp = m_top;
    m_top = m_top->next;
}

std::shared_ptr<ThoughtNode> Idea::getTop() const
{
    return m_top;
}

String Idea::getTitle() const
{
    return m_Title;
}

void Idea::setTitle(const String& title)
{
    m_Title = title;
}

bool Idea::isDone() const
{
    return m_Done;
}

void Idea::setStatus(const bool stat)
{
    m_Done = stat;
}

void Idea::display(const std::shared_ptr<ThoughtNode>& p) const
{
    if (!p)
        return;
    display(p->next);
    std::cout << "- " << p->phrase.c_str() << std::endl;
}

} // namespace Mapper
