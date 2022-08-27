#ifndef PAFA_INCLUDE_ALIAS_H
#define PAFA_INCLUDE_ALIAS_H

#include <string>
#include <unordered_set>

namespace PAFa {
struct pred {
    bool operator()(const std::pair<std::string, std::string> &pair1,
                    const std::pair<std::string, std::string> &pair2) const {
        if (pair1.first == pair2.first) return pair1.second == pair2.second;
        if (pair1.second == pair2.first) return pair1.first == pair2.second;
        return false;
    }
};
struct hash {
    std::size_t operator()(const std::pair<std::string, std::string> &pair) const {
        return std::hash<std::string>{}(pair.first) ^ std::hash<std::string>{}(pair.second);
    }
};
using SetOverlaps = std::unordered_set<std::pair<std::string, std::string>, hash, pred>;
} // namespace PAFa
#endif //PAFA_INCLUDE_ALIAS_H
