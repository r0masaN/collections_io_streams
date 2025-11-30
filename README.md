# collections_io_streams
Simple C++ library that complements 'std' by adding custom overloading for '&lt;&lt;' and '>>' operators in 'iostream' for standard collections ('vector', 'map', etc.)

## Usage for 'ostream'
1. depending on collection type, '#define \[COLLECTION\]_PREFIX/DELIMITER/POSTFIX "..."' if you need custom prefix, delimiter or postfix (by default it's "\[", ", " and "\]" for all collections and "{", ": " and "}" for 'pair')
2. #include needed header ('\[collection\]_ostream.hpp')
3. easily print selected collection with any 'ostream' with '<<' like default types
 
