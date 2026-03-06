#ifndef IDEA_H
#define IDEA_H

#include <memory>
#include "utils/String.h"

namespace Mapper {

class ThoughtNode final
{
public:
    String phrase;
    std::shared_ptr<ThoughtNode> next;

    ThoughtNode(const String& str) : phrase(str), next(nullptr) {}

    ThoughtNode(const ThoughtNode& other) : phrase(other.phrase), next(other.next) {}

    ThoughtNode& operator=(const ThoughtNode& other) {
        if (this == &other)
            return *this;
        phrase = other.phrase;
        next = other.next;
        return *this;
    }

    ~ThoughtNode() = default;
};

class Idea final
{
private:
    std::shared_ptr<ThoughtNode> m_top;
    String m_Title;
    bool m_Done;

public:
    Idea(); // Default constructor
    Idea(const String& title); // Construct a titled idea
    Idea(const Idea& other); // Copy Constructor
    Idea& operator=(const Idea& other); // Copy assignment operator
    ~Idea() = default;

    void push(const String& s); // Add a new thought to idea
    void pop(); // Pop last thought from idea
    std::shared_ptr<ThoughtNode> getTop() const; // Return a pointer to top thought in idea
    String getTitle() const; // Return idea title
    void setTitle(const String& title); // set title of idea
    bool isDone() const; // is idea done?
    void setStatus(const bool stat); // set status of idea (enum needed?)
    void display(const std::shared_ptr<ThoughtNode>& p) const; // display the thoughts in this idea
};
} // namespace Mapper

#endif // IDEA_H
