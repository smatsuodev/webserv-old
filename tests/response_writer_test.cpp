#include "fakeit.hpp"
#include "http/response_writer.hpp"
#include <gtest/gtest.h>

using namespace fakeit;

TEST(ResponseWriterTest, sendToFd) {
    Mock<IOTaskManager> manager;
    int fd = 1;
    ResponseWriter<int> writer(manager.get(), fd);

    Fake(Method(manager, addTask));

    writer.writeBody("Hello, world!");
    writer.send<WriteFileCallback>();

    Verify(Method(manager, addTask)).Exactly(1);
}

TEST(ResponseWriterTest, sendShortBodyToOStream) {
    IOTaskManager manager;
    std::ostringstream output;
    ResponseWriter<std::ostream &> writer(manager, output);

    writer.writeBody("Hello, world!");
    writer.send();

    EXPECT_EQ("HTTP/1.1 200 OK\nContent-Length: 13\n\r\nHello, world!", output.str());
}

TEST(ResponseWriterTest, sendLongBodyToOStream) {
    IOTaskManager manager;
    std::ostringstream output;
    ResponseWriter<std::ostream &> writer(manager, output);

    std::string long_body(1000, 'a');
    writer.writeBody(long_body);
    writer.send();

    std::string expected = "HTTP/1.1 200 OK\nContent-Length: 1000\n\r\n" + long_body;
    EXPECT_EQ(expected, output.str());
}

TEST(ResponseWriterTest, sendHeadersToOStream) {
    IOTaskManager manager;
    std::ostringstream output;
    ResponseWriter<std::ostream &> writer(manager, output);

    writer.writeHeader("Content-Type", "text/plain");
    writer.send();

    std::string expected = "HTTP/1.1 200 OK\nContent-Length: 0\nContent-Type: text/plain\n\r\n";
    EXPECT_EQ(expected, output.str());
}

TEST(ResponseWriterTest, sendStatusToOStream) {
    IOTaskManager manager;
    std::ostringstream output;
    ResponseWriter<std::ostream &> writer(manager, output);

    writer.setStatus(HttpStatusCode::kStatusNotFound);
    writer.send();

    std::string expected = "HTTP/1.1 404 Not Found\nContent-Length: 0\n\r\n";
    EXPECT_EQ(expected, output.str());
}
