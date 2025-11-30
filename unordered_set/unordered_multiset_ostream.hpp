#ifndef UNORDERED_MULTISET_OSTREAM_HPP
#define UNORDERED_MULTISET_OSTREAM_HPP

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
inline std::ostream& operator<<(std::ostream& os, const std::unordered_multiset<T>& ums) {
    os << SET_PREFIX;
    for (typename std::unordered_multiset<T>::iterator it = ums.begin(); it != ums.end(); ++it) {
        if (it != ums.begin()) os << SET_DELIMITER;
        os << *it;
    }
    os << SET_POSTFIX;

    return os;
}

#endif
