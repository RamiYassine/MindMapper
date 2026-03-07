#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <nlohmann/json.hpp>
#include "../MindMapper.h"

using json = nlohmann::json;

namespace Mapper {

inline void to_json(json& j, const String& str)
{
	j = std::string(str.c_str());
}

inline void from_json(const json& j, String& str)
{
    str = String(j.get<std::string>().c_str());
}

inline void to_json(json& j, const ThoughtNode& t)
{
    j = json {
        {
            "phrase", t.phrase
        }
    };
}

inline void from_json(const json& j, ThoughtNode& t)
{
    String phrase;
    j.at("phrase").get_to(phrase);
    t = ThoughtNode(phrase);
}

inline void to_json(json& j, const Idea& i)
{
    // Serialize all thoughts as an array
    std::vector<ThoughtNode> thoughts;
    auto curr = i.getTop();
    while (curr) {
        thoughts.push_back(*curr);
        curr = curr->next;
    }
    // Reverse to preserve stack order (bottom to top)
    std::reverse(thoughts.begin(), thoughts.end());
    j = json {
        {
            "title",
            i.getTitle()
        },
        {
            "done",
            i.isDone()
        },
        {
            "thoughts",
            thoughts
        }
    };
}

inline void from_json(const json& j, Idea& i)
{
    // Get title and done status
    String title = j.at("title").get<String>();
    i = Idea(title);
    bool done = j.at("done").get<bool>();
    i.setStatus(done);
    const auto& thoughts_array = j.at("thoughts");
    for (const auto& t : thoughts_array) {
        i.push(t.at("phrase").get<String>());
    }
}

inline void to_json(json& j, const IdeaNode& in) 
{
    j = json {
        {
            "idea",
            in.idea
        }
    };
}

inline void from_json(const json& j, IdeaNode& in)
{
    Idea s = j.at("idea").get<Idea>();
    in = IdeaNode(s);
}

inline void to_json(json& j, const MindMapper& m)
{
    std::vector<IdeaNode> ideas;
    auto curr = m.getFirst();
    while (curr) {
        ideas.push_back(*curr);
        curr = curr->next;
    }
    j = json {
        {
            "ideas",
            ideas
        },
        {
            "length",
            m.getIdeaCount()
        }
    };
}

inline void from_json(const json& j, MindMapper& m)
{
    for (const auto& jidea : j.at("ideas")) {
        Idea s = jidea.at("idea").get<Idea>();
        m.addIdea(s);  // directly add stack without needing Idea default constructor
    }
}

}

#endif // SERIALIZATION_H
