#ifndef INITIALIZER_LIST_OSTREAM_HPP
#define INITIALIZER_LIST_OSTREAM_HPP

#include <ostream>
#include <initializer_list>

#ifndef INITIALIZER_LIST_PREFIX
#define INITIALIZER_LIST_PREFIX "["
#endif

#ifndef INITIALIZER_LIST_DELIMITER
#define INITIALIZER_LIST_DELIMITER ", "
#endif

#ifndef INITIALIZER_LIST_POSTFIX
#define INITIALIZER_LIST_POSTFIX "]"
#endif

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::initializer_list<T>& il) {
    os << INITIALIZER_LIST_PREFIX;
    for (typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it) {
        if (it != il.begin()) os << INITIALIZER_LIST_DELIMITER;
        os << *it;
    }
    os << INITIALIZER_LIST_POSTFIX;

    return os;
}

#endif
