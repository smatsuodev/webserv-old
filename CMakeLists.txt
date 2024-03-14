cmake_minimum_required(VERSION 3.11)
project(webserv)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fsanitize=address,undefined --coverage")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(CLANG_TIDY clang-tidy)
if (CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif ()

enable_testing()

include_directories(internal)

add_subdirectory(internal)
add_subdirectory(tests)

add_executable(webserv cmd/webserv.cpp)
target_link_libraries(webserv webserv_internal)
target_include_directories(webserv PRIVATE internal)
