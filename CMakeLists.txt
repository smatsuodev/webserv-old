cmake_minimum_required(VERSION 3.27)
project(echo_server)

set(CMAKE_CXX_STANDARD 98)

file(GLOB SRC *.hpp *cpp)

add_executable(echo_server ${SRC})
target_compile_options(echo_server PUBLIC -Wall -Wextra -Werror -g -fsanitize=address)
target_link_options(echo_server PUBLIC -fsanitize=address)
