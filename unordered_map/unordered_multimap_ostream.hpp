#ifndef UNORDERED_MULTIMAP_OSTREAM_HPP
#define UNORDERED_MULTIMAP_OSTREAM_HPP

#include <ostream>
#include <unordered_map>
#include "../pair/pair_ostream.hpp"

#ifndef MAP_PREFIX
#define MAP_PREFIX "["
#endif

#ifndef MAP_DELIMITER
#define MAP_DELIMITER ", "
#endif

#ifndef MAP_POSTFIX
#define MAP_POSTFIX "]"
#endif

template<typename K, typename V>
inline std::ostream& operator<<(std::ostream& os, const std::unordered_multimap<K, V>& umm) {
    os << MAP_PREFIX;
    for (typename std::unordered_multimap<K, V>::iterator it = umm.begin(); it != umm.end(); ++it) {
        if (it != umm.begin()) os << MAP_DELIMITER;
        os << *it;
    }
    os << MAP_POSTFIX;

    return os;
}

#endif
