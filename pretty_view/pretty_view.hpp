#ifndef PRETTY_VIEW_HPP
#define PRETTY_VIEW_HPP

#include <concepts>
#include <type_traits>
#include <string>
#include <string_view>
#include <tuple>
#include <ostream>

namespace rmsn {
    // global variables used in pretty_view.operator<<
    namespace pretty_view_helper {
        static const char *collection_prefix = "[", *collection_postfix = "]", *collection_delimiter = ", ",
            *tuple_prefix = "{", *tuple_postfix = "}", *tuple_delimiter = ", ";
    }

    // get pure, clear type (without const, volatile qualifiers, reference)
    template<typename T>
    using base_t = std::remove_cvref_t<T>;

    // is the type is a string-like (need to ensure that we won't write a string-like type char by char like it's array of chars)
    template<typename T>
    concept is_string = std::is_convertible_v<base_t<T>, std::string> || std::is_convertible_v<base_t<T>, std::string_view>;

    // is the type is a collection-like (has iterators)
    template<typename T>
    concept is_collection = requires (const base_t<T>& t) {
        std::begin(t); // unified way to get an iterator (instead of simple t.begin() that, for example, couldn't be
        std::end(t); // invoked on raw arrays
    } && !is_string<T>; // cuz std::string, std::string_view, char arrays, const char * also can get iterators

    // is the type is a tuple-like (can invoke std::get<N>(), std::tuple_size<T>)
    template<typename T>
    concept is_tuple = requires {
        std::tuple_size<base_t<T>>::value;
    };

    // simple proxy class for collections and tuples (to prevent ADL from breaking overloadings or messing with some shit in std)
    template<typename T>
    requires (is_collection<T> || is_tuple<T>)
    struct pretty_view {
        explicit pretty_view(const T& t) noexcept : _t(t) {}

        friend std::ostream& operator<<(std::ostream& os, const pretty_view<T>& pv) noexcept {
            if constexpr (is_collection<T>) { // if proxy contains collection
                os << pretty_view_helper::collection_prefix;

                const auto begin = std::begin(pv._t), end = std::end(pv._t);
                using elem_t = base_t<decltype(*begin)>; // dirty type (I don't care cuz it will be cleaned in concepts)

                for (auto it = begin; it != end; ++it) { // iterating on collection
                    if (it != begin) os << pretty_view_helper::collection_delimiter;
                    // if collection's element is collection or tuple himself
                    if constexpr (is_collection<elem_t> || is_tuple<elem_t>) os << pretty_view<elem_t>(*it); // wrap in proxy => recursion
                    else os << *it; // else it's primitive or class/struct that isn't collection/tuple
                }

                os << pretty_view_helper::collection_postfix;

            } else if constexpr (is_tuple<T>) { // if proxy contains tuple
                os << pretty_view_helper::tuple_prefix;

                // fun :) it's anonymous lambda that's unwrapping index sequence made from tuple
                [&]<std::size_t... I>(std::index_sequence<I...>) {
                    ( // 67-77 lines will be applied for each unwrapped element from tuple
                            ( // if that's the first element of tuple, don't write delimiter (before him)
                                    I == 0 ? void() : void(os << pretty_view_helper::tuple_delimiter),
                                    [&]() { // another anonymous lambda that does the same logic that 52-57 lines
                                        const auto& elem = std::get<I>(pv._t); // std::get<I>(pv._t) gets an I-st element from tuple pv.t
                                        using elem_t = decltype(elem);
                                        if constexpr (is_collection<elem_t> || is_tuple<elem_t>) os << pretty_view<elem_t>(elem);
                                        else os << elem;
                                    }() // immediately invoke this lambda
                            ),
                            ... // unwrapping variadic pack
                    );
                }(std::make_index_sequence<std::tuple_size_v<base_t<T>>>{}); // here comes an index sequence + immediately invocation

                os << pretty_view_helper::tuple_postfix;
            } // there are no other if-else branches cuz we work here only with collections and tuples

            return os;
        }

    private:
        const T& _t;
    };
}

#endif
