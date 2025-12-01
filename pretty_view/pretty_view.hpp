#ifndef PRETTY_VIEW_HPP
#define PRETTY_VIEW_HPP

#include <concepts>
#include <type_traits>
#include <string>
#include <string_view>
#include <tuple>
#include <ostream>

namespace rmsn {
    // get pure, clear type (without const, volatile qualifiers, reference)
    template<typename T>
    using base_t = std::remove_cvref_t<T>;

    // is the type is a string-like (need to ensure that we won't write a string-like type char by char like it's array of chars)
    template<typename T>
    concept is_str_like = std::is_convertible_v<base_t<T>, std::string> || std::is_convertible_v<base_t<T>, std::string_view>;

    // is the type is a collection-like (has iterators)
    template<typename T>
    concept is_col_like = requires (base_t<T>& t) {
        std::begin(t); // unified way to get an iterator (instead of simple t.begin() that, for example, couldn't be
        std::end(t); // invoked on raw arrays
    } && !is_str_like<T>; // cuz std::string, std::string_view, char arrays, const char * also can get iterators

    // is the type is a tuple-like (can invoke std::get<N>(t), std::tuple_size<T>)
    template<typename T>
    concept is_tup_like = requires {
        std::tuple_size<base_t<T>>::value;
    };

    // simple proxy class for collections and tuples (to prevent ADL from breaking overloadings or messing with some shit in std)
    template<typename T>
    requires ((is_col_like<T> || is_tup_like<T>) && ! is_str_like<T>)
    struct pretty_view {
        const T& t; // pref = prefix, post = postfix, delim - delimiter, col = collection, tup = tuple
        const char *col_pref = "[", *col_delim = ", ", *col_post = "]", *tup_pref = "{", *tup_delim = ", ", *tup_post = "}";
    };

    // requirements just in case
    template<typename T>
    requires ((is_col_like<T> || is_tup_like<T>) && ! is_str_like<T>)
    std::ostream& operator<<(std::ostream& os, const pretty_view<T>& pv) {
        if constexpr (is_col_like<T>) { // if proxy contains collection
            os << pv.col_pref;

            const auto begin = std::begin(pv.t), end = std::end(pv.t);
            for (auto it = begin; it != end; ++it) { // iterating on collection
                if (it != begin) os << pv.col_delim;

                using elem_t = decltype(*it); // dirty type (I don't care cuz it will be cleaned in concepts)
                if constexpr (is_col_like<elem_t> || is_tup_like<elem_t>) { // if collection's element is collection or tuple himself
                    os << pretty_view{*it, pv.col_pref, pv.col_delim, pv.col_post, pv.tup_pref, pv.tup_delim, pv.tup_post}; // wrap in proxy => recursion
                } else { // else it's primitive or class/struct that isn't collection/tuple
                    os << *it;
                }
            }

            os << pv.col_post;

        } else if constexpr (is_tup_like<T>) { // if proxy contains tuple
            os << pv.tup_pref;
            // fun :) it's anonymous lambda that's unwrapping index sequence made from tuple
            [&]<std::size_t... I>(std::index_sequence<I...>) {
                ( // 67-77 lines will be applied for each unwrapped element from tuple
                        ( // if that's the first element of tuple, don't write delimiter (before him)
                                (I == 0 ? void() : void(os << pv.tup_delim)),
                                        ([&]() { // another anonymous lambda that does the same logic that 52-57 lines
                                            using elem_t = decltype(std::get<I>(pv.t)); // std::get<I>(pv.t) gets an I-st element from tuple pv.t
                                            if constexpr (is_col_like<elem_t> || is_tup_like<elem_t>) {
                                                os << pretty_view{std::get<I>(pv.t), pv.col_pref, pv.col_delim, pv.col_post, pv.tup_pref, pv.tup_delim, pv.tup_post};
                                            } else {
                                                os << std::get<I>(pv.t);
                                            }
                                        }()) // immediately invoke this lambda
                        ),
                        ... // unwrapping variadic pack
                );
            }(std::make_index_sequence<std::tuple_size_v<base_t<T>>>{}); // here comes an index sequence + immediately invocation

            os << pv.tup_post;
        } // there are no other if-else branches cuz we work here only with collections and tuples

        return os;
    }
}

#endif
