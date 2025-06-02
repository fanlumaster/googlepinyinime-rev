cmake_minimum_required(VERSION 3.15)

project(pinyinime VERSION 1.0 LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_definitions(
    /D_UNICODE=1
    /DUNICODE=1
)

# For utf8cpp, make it use C++11 and later
add_compile_options(/Zc:__cplusplus)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# For pure-header libs installed by vcpkg like utf8cpp
include_directories("./build/vcpkg_installed/x64-windows/include")

set(HEADERS
    ./src/include/atomdictbase.h
    ./src/include/dictbuilder.h
    ./src/include/dictdef.h
    ./src/include/dictlist.h
    ./src/include/dicttrie.h
    ./src/include/lpicache.h
    ./src/include/matrixsearch.h
    ./src/include/mystdlib.h
    ./src/include/ngram.h
    ./src/include/pinyinime.h
    ./src/include/searchutility.h
    ./src/include/spellingtable.h
    ./src/include/spellingtrie.h
    ./src/include/splparser.h
    ./src/include/sync.h
    ./src/include/userdict.h
    ./src/include/utf16char.h
    ./src/include/utf16reader.h
)

set(SOURCES
    ./src/share/dictbuilder.cpp
    ./src/share/dictlist.cpp
    ./src/share/dicttrie.cpp
    ./src/share/lpicache.cpp
    ./src/share/matrixsearch.cpp
    ./src/share/mystdlib.cpp
    ./src/share/ngram.cpp
    ./src/share/pinyinime.cpp
    ./src/share/searchutility.cpp
    ./src/share/spellingtable.cpp
    ./src/share/spellingtrie.cpp
    ./src/share/splparser.cpp
    ./src/share/sync.cpp
    ./src/share/userdict.cpp
    ./src/share/utf16char.cpp
    ./src/share/utf16reader.cpp
    ./tests/main.cpp
)

set(MY_EXECUTABLE_NAME "pinyinime")

add_executable(pinyinime ${SOURCES} ${HEADERS})