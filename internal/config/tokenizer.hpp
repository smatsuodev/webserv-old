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
private:
    std::map<TokenType, std::string> token_type_map_;
};

#endif