#ifndef WEBSERV_ASSERT_OUTPUT_HPP
#define WEBSERV_ASSERT_OUTPUT_HPP

#include <string>
#include <sstream>
#include <gtest/gtest.h>

template<typename F>
std::string capture_output(std::ostream &os, F &&f) {
	// Backup original buffer and redirect stream to out buffer
	std::stringstream ss;
	std::streambuf *old = os.rdbuf(ss.rdbuf());

	f();

	// Restore original buffer
	os.rdbuf(old);

	return ss.str();
}

template<typename F, typename... Args>
void assert_stdout(const std::string &expected, F &&f, Args &&... args) {
	auto lambda = [&]() {
		return f(args...);
	};

	const std::string output = capture_output(std::cout, lambda);

	ASSERT_EQ(output, expected);
}

template<typename F, typename... Args>
void assert_stderr(const std::string &expected, F &&f, Args &&... args) {
	auto lambda = [&]() {
		return f(args...);
	};

	const std::string output = capture_output(std::cerr, lambda);

	ASSERT_EQ(output, expected);
}

#endif //WEBSERV_ASSERT_OUTPUT_HPP
