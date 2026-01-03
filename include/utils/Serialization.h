#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <nlohmann/json.hpp>
#include "../MindMapper.h"

using json = nlohmann::json;

namespace Mapper {
inline void to_json(json& j, const String& str) {
	j = std::string(str.c_str());
}

inline void to_json(json& j, const Thought& t) {
    j = json {
        {
            "phrase", t.phrase
        }
    };
}

inline void to_json(json& j, const Stack& s) {
    // Serialize all thoughts as an array
    std::vector<Thought> thoughts;
    Thought* curr = s.getTop();
    while (curr) {
        thoughts.push_back(*curr);
        curr = curr->next;
    }
    // Reverse to preserve stack order (bottom to top)
    std::reverse(thoughts.begin(), thoughts.end());
    j = json {
        {
            "title",
            s.getTitle()
        },
        {
            "done",
            s.isDone()
        },
        {
            "thoughts",
            thoughts
        }
    };
}

inline void to_json(json& j, const Idea& i) {
    j = json {
        {
            "thoughts",
            i.thoughts
        }
    };
}

inline void to_json(json& j, const MindMapper& m) {
    std::vector<Idea> ideas;
    const Idea* curr = m.getFirst();
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

}

#endif // SERIALIZATION_H
