cmake_minimum_required(VERSION 3.16)

project("list")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(list tests.cpp list.h list.cpp)

target_compile_options(list PUBLIC -fsanitize=address,undefined,leak)
 target_link_options(list PUBLIC -fsanitize=address,undefined,leak)
