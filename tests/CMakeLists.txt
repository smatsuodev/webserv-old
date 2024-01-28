project(webserv_tests)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Google Test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 # v1.14.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# FakeIt
FetchContent_Declare(
        fakeit
        GIT_REPOSITORY https://github.com/eranpeer/FakeIt.git
        GIT_TAG cb39d8a053876f74dfeed66dd335d3041f142095 # 2.4.0
)
FetchContent_MakeAvailable(fakeit)

include_directories(${CMAKE_SOURCE_DIR}/internal)
include_directories(utils)

link_libraries(webserv_internal gtest_main FakeIt::FakeIt-gtest)

# Utils
# Uncomment if you want to use test_utils
#add_library(tests_utils STATIC )
#link_libraries(test_utils)

# Tests
add_executable(hello_test hello_test.cpp)
gtest_discover_tests(hello_test)
