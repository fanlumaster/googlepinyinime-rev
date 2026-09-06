cmake_minimum_required(VERSION 3.25)
project(pinyin_decoder_tests LANGUAGES CXX)
include(CTest)
file(GLOB decoder_sources CONFIGURE_DEPENDS "../src/share/*.cpp")
list(FILTER decoder_sources EXCLUDE REGEX "/maintest\\.cpp$")
add_library(pinyin_decoder STATIC ${decoder_sources})
target_compile_features(pinyin_decoder PUBLIC cxx_std_17)
target_include_directories(pinyin_decoder PUBLIC ../src/include)
add_executable(decoder_smoke decoder_smoke.cpp)
target_link_libraries(decoder_smoke PRIVATE pinyin_decoder)
add_test(NAME decoder_smoke COMMAND decoder_smoke
    "${CMAKE_CURRENT_SOURCE_DIR}/../data/dict_pinyin.dat"
    "${CMAKE_CURRENT_BINARY_DIR}/test-user.dat")
