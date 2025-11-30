#ifndef LIST_OSTREAM_HPP
#define LIST_OSTREAM_HPP

#include <ostream>
#include <list>

#ifndef LIST_PREFIX
#define LIST_PREFIX "["
#endif

#ifndef LIST_DELIMITER
#define LIST_DELIMITER ", "
#endif

#ifndef LIST_POSTFIX
#define LIST_POSTFIX "]"
#endif

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::list<T>& l) {
    os << LIST_PREFIX;
    for (typename std::list<T>::iterator it = l.begin(); it != l.end(); ++it) {
        if (it != l.begin()) os << LIST_DELIMITER;
        os << *it;
    }
    os << LIST_POSTFIX;

    return os;
}

#endif
