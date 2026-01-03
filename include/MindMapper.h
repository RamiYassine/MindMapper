#ifndef MIND_MAPPER_H
#define MIND_MAPPER_H

#include "Stack.h"

namespace Mapper {

class Idea final
{
public:
    Stack thoughts;
    Idea *next;

    Idea(const Stack& stk) {
        thoughts = stk;
        next = nullptr;
    }
};

class MindMapper final
{
public:
    MindMapper();
    ~MindMapper();

    void run();
    void traverseIdeas() const;
    const Idea* getFirst() const;
    int getIdeaCount() const;
    // void traverseThoughts();
private:
    Idea *m_first;
    Idea *m_last;
    int m_Length;
    
    void mainMenu() const;
    void thinkMenu() const;
    void formIdea();
    void addIdea(const Stack& stk);
    void removeIdea();
    void editIdea();
    void markIdeaDone();
    int selectIdea();
    void loadOrSave();
    void serialize(const std::string& filename);
    static MindMapper deserialize(const std::string& filename);
};
} // namespace Mapper

#endif // MIND_MAPPER_H
