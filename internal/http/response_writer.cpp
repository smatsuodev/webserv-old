#include "response_writer.hpp"

template<>
void ResponseWriter<int>::send() {
    new WriteFile(manager_, output_, generateRawResponseText(), new WriteFileCallback(output_));
}

// This function is for testing purposes only.
template<>
void ResponseWriter<std::ostream &>::send() {
    std::string raw_response = generateRawResponseText();
    output_ << raw_response;
}
