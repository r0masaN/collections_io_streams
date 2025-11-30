#ifndef FORWARD_LIST_OSTREAM_HPP
#define FORWARD_LIST_OSTREAM_HPP

#include <ostream>
#include <forward_list>

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
inline std::ostream& operator<<(std::ostream& os, const std::forward_list<T>& fl) {
    os << LIST_PREFIX;
    for (typename std::forward_list<T>::iterator it = fl.begin(); it != fl.end(); ++it) {
        if (it != fl.begin()) os << LIST_DELIMITER;
        os << *it;
    }
    os << LIST_POSTFIX;

    return os;
}


#endif
