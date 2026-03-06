#ifndef MIND_MAPPER_H
#define MIND_MAPPER_H

#include "Idea.h"

namespace Mapper {

class IdeaNode final
{
public:
    Idea idea;
    std::shared_ptr<IdeaNode> next;

    IdeaNode(const Idea& id) : idea(id), next(nullptr) {}

    IdeaNode(const IdeaNode& other) : idea(other.idea), next(other.next) {}

    IdeaNode& operator=(const IdeaNode& other) {
        if (this == &other)
            return *this;
        idea = other.idea;
        next = other.next;
        return *this;
    }

    ~IdeaNode() = default;
};

class MindMapper final
{
private:
    std::shared_ptr<IdeaNode> m_first;
    std::shared_ptr<IdeaNode> m_last;
    int m_Length;
    
    void mainMenu() const;
    void thinkMenu() const;
    void formIdea();
    void removeIdea();
    void editIdea();
    void markIdeaDone();
    int selectIdea();
    void loadOrSave();
    void serialize(const std::string& filename);
    static MindMapper deserialize(const std::string& filename);

public:
    MindMapper();
    ~MindMapper();

    void run();
    void traverseIdeas() const;
    const std::shared_ptr<IdeaNode> getFirst() const;
    int getIdeaCount() const;
    void addIdea(const Idea& stk);
    // void traverseThoughts();
};
} // namespace Mapper

#endif // MIND_MAPPER_H
