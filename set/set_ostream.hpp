#ifndef SET_OSTREAM_HPP
#define SET_OSTREAM_HPP

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
inline std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << SET_PREFIX;
    for (typename std::set<T>::iterator it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) os << SET_DELIMITER;
        os << *it;
    }
    os << SET_POSTFIX;

    return os;
}

#endif
