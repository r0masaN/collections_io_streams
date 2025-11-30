#ifndef VECTOR_OSTREAM_HPP
#define VECTOR_OSTREAM_HPP

#include <ostream>
#include <vector>

#ifndef VECTOR_PREFIX
#define VECTOR_PREFIX "["
#endif

#ifndef VECTOR_DELIMITER
#define VECTOR_DELIMITER ", "
#endif

#ifndef VECTOR_POSTFIX
#define VECTOR_POSTFIX "]"
#endif

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << VECTOR_PREFIX;
    for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
        if (it != v.begin()) os << VECTOR_DELIMITER;
        os << *it;
    }
    os << VECTOR_POSTFIX;

    return os;
}

#endif
