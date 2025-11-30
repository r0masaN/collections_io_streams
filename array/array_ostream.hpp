#ifndef ARRAY_OSTREAM_HPP
#define ARRAY_OSTREAM_HPP

#include <ostream>
#include <array>

#ifndef ARRAY_PREFIX
#define ARRAY_PREFIX "["
#endif

#ifndef ARRAY_DELIMITER
#define ARRAY_DELIMITER ", "
#endif

#ifndef ARRAY_POSTFIX
#define ARRAY_POSTFIX "]"
#endif

template<typename T, size_t S>
inline std::ostream& operator<<(std::ostream& os, const std::array<T, S>& a) {
    os << ARRAY_PREFIX;
    for (typename std::array<T, S>::iterator it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) os << ARRAY_DELIMITER;
        os << *it;
    }
    os << ARRAY_POSTFIX;

    return os;
}

#endif
