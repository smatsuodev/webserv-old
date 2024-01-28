#include "assert_output.hpp"
#include "hello/hello.hpp"

TEST(hello_test, output) {
	assert_stdout("Hello, World!\n", hello);
}