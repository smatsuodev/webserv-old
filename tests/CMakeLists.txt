project(webserv_tests)

set(CMAKE_CXX_STANDARD 17)

# Google Test v1.14.0
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

include_directories(${CMAKE_SOURCE_DIR}/internal)
include_directories(utils)

link_libraries(webserv_internal gtest_main)

# Utils
# Uncomment if you want to use test_utils
#add_library(tests_utils STATIC )
#link_libraries(test_utils)

# Tests
add_executable(hello_test hello_test.cpp)
gtest_discover_tests(hello_test)