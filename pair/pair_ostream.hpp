#ifndef PAIR_OSTREAM_HPP
#define PAIR_OSTREAM_HPP

#include <ostream>
#include <utility>

#ifndef PAIR_PREFIX
#define PAIR_PREFIX "{"
#endif

#ifndef PAIR_DELIMITER
#define PAIR_DELIMITER ": "
#endif

#ifndef PAIR_POSTFIX
#define PAIR_POSTFIX "}"
#endif

template<typename K, typename V>
inline std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& p) {
    os << PAIR_PREFIX << p.first << PAIR_DELIMITER << p.second << PAIR_POSTFIX;

    return os;
}

#endif
