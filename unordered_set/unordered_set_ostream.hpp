#ifndef UNORDERED_SET_OSTREAM_HPP
#define UNORDERED_SET_OSTREAM_HPP

#include <ostream>
#include <unordered_set>

#ifndef SET_PREFIX
#define SET_PREFIX "["
#endif

#ifndef SET_DELIMITER
#define SET_DELIMITER ", "
#endif

#ifndef SET_POSTFIX
#define SET_POSTFIX "]"
#endif

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& us) {
    os << SET_PREFIX;
    for (typename std::unordered_set<T>::iterator it = us.begin(); it != us.end(); ++it) {
        if (it != us.begin()) os << SET_DELIMITER;
        os << *it;
    }
    os << SET_POSTFIX;

    return os;
}

#endif
