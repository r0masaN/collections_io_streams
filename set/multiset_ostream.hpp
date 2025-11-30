#ifndef MULTISET_OSTREAM_HPP
#define MULTISET_OSTREAM_HPP

#include <ostream>
#include <set>

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
inline std::ostream& operator<<(std::ostream& os, const std::multiset<T>& ms) {
    os << SET_PREFIX;
    for (typename std::multiset<T>::iterator it = ms.begin(); it != ms.end(); ++it) {
        if (it != ms.begin()) os << SET_DELIMITER;
        os << *it;
    }
    os << SET_POSTFIX;

    return os;
}

#endif
