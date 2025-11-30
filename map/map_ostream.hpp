#ifndef MAP_OSTREAM_HPP
#define MAP_OSTREAM_HPP

#include <ostream>
#include <map>
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
inline std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << MAP_PREFIX;
    for (typename std::map<K, V>::iterator it = m.begin(); it != m.end(); ++it) {
        if (it != m.begin()) os << MAP_DELIMITER;
        os << *it;
    }
    os << MAP_POSTFIX;

    return os;
}

#endif
