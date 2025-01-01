cmake_minimum_required(VERSION 3.15)  # Qt6 需要 CMake 3.15 或更高版本

# 设置项目名称和版本
project(pinyinime VERSION 1.0 LANGUAGES CXX)

# 包含头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置 C 标准为 C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# 添加头文件
set(HEADERS
    atomdictbase.h
    dictbuilder.h
    dictdef.h
    dictlist.h
    dicttrie.h
    lpicache.h
    matrixsearch.h
    mystdlib.h
    ngram.h
    pinyinime.h
    searchutility.h
    spellingtable.h
    spellingtrie.h
    splparser.h
    sync.h
    userdict.h
    utf16char.h
    utf16reader.h
)

# 添加源文件
set(SOURCES
    dictbuilder.cpp
    dictlist.cpp
    dicttrie.cpp
    lpicache.cpp
    matrixsearch.cpp
    mystdlib.cpp
    ngram.cpp
    pinyinime.cpp
    searchutility.cpp
    spellingtable.cpp
    spellingtrie.cpp
    splparser.cpp
    sync.cpp
    userdict.cpp
    utf16char.cpp
    utf16reader.cpp
    main.cpp
)

# 创建库
add_executable(pinyinime ${SOURCES} ${HEADERS})
# add_executable(pinyinime "./maintest.cpp")

# 如果需要安装，可以添加 install 命令
# install(TARGETS pinyinime DESTINATION lib)