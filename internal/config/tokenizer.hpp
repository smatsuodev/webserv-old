#ifndef TOKENIZER_HPP
# define TOKENIZER_HPP

#include <iostream>
#include <map>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include <vector>

enum TokenType {
    kUnknown,
    kDirective,
    kBlockStart,
    kBlockEnd,
    kString,
    kNumber,
    kSemicolon,
    kComment,
};

class Tokenizer {
public:
    Tokenizer(const std::string &path);
    ~Tokenizer();

    std::vector<std::pair<std::string, std::string> > common_config_blocks_;
    std::vector<std::pair<std::string, std::string> > server_config_blocks_;
    std::vector<std::vector<std::pair<std::string, std::string> > > route_config_blocks_;
};

#endif