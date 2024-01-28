cmake_minimum_required(VERSION 3.5)
project(webserv)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fsanitize=address,undefined")

enable_testing()

add_subdirectory(internal)
add_subdirectory(tests)

add_executable(webserv cmd/webserv.cpp)
target_link_libraries(webserv webserv_internal)
target_include_directories(webserv PRIVATE internal)
