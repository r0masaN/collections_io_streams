# collections_io_streams
Simple C++ library that complements 'std' by adding custom overloading for '&lt;&lt;' and '>>' operators in 'iostream' for standard collections ('vector', 'map', etc.)

## Usage for 'ostream'
0. if you use your custom type 'T', you should write your own overloading 'std::ostream& operator<<(std::ostream&, T&)' for correct work!
1. depending on collection type, '#define \[COLLECTION\]_PREFIX/DELIMITER/POSTFIX "..."' if you need custom prefix, delimiter or postfix (by default it's "\[", ", " and "\]" for all collections and "{", ": " and "}" for 'pair')
2. #include needed header ('\[collection\]_ostream.hpp')
3. easily print selected collection with any 'ostream' with '<<' like default types

## UPD:
Everything in all folders **except** `pretty_view` is bullshit for toddlers from kindergarten)
The **real** unified tool for cozy writing in ostream is pretty_view.hpp thing) it's freaking wild.
And I've spent literally 6+ hours in a row for this 🤪

## Usage of the `pretty_view`
```c++
std::ostream << rmsn::pretty_view(N);
```
where N is any collection or tuple-like thing (thanks to ADL nothing bad happens with this overloading)
Structure of struct `pretty_view`:
```c++
struct pretty_view {
    const T& _t;
};
```
Also there are helping nested namespace `pretty_view_helper`:
```c++
namespace pretty_view_helper {
    static const char *collection_prefix = "[", *collection_postfix = "]", *collection_delimiter = ", ",
        *tuple_prefix = "{", *tuple_postfix = "}", *tuple_delimiter = ", ";
}
```
Ofc you can set all of these parameters by yourself
