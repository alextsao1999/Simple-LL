cmake_minimum_required(VERSION 3.10)
project(SimpleLL)
set(CMAKE_CXX_STANDARD 14)

add_library(simplell INTERFACE)
target_include_directories(simplell INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test main.cpp)
target_link_libraries(test simplell)