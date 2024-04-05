#include "tokenizer.hpp"

static std::vector<std::string> getConfString(const std::string &path) {
    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
    }
    struct stat st = {};
    fstat(fd, &st);
    size_t size = st.st_size;
    char *buf = (char *)mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf == MAP_FAILED) {
        std::cerr << "Cannot mmap file" << std::endl;
        exit(1);
    }
    close(fd);
    std::string s(buf, size);
    munmap(buf, size);
    std::vector<std::string> lines;
    std::stringstream ss(s);
    std::string line;
    while (std::getline(ss, line)) {
        size_t pos = line.find('#');
        if (pos != std::string::npos) {
            line = line.substr(0, pos);
        }
        lines.push_back(line);
    }
    return lines;
}

Tokenizer::Tokenizer(const std::string &path) {
    std::vector<std::string> input = getConfString(path);
    std::vector<std::pair<std::string, std::string> > blocks;
    for (const auto &line : input) {
        std::string key, value;
        if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
            continue;
        }
        // 最初に登場する '=' で分割
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            key = line.substr(0, pos);
            value = line.substr(pos + 1);
            value.erase(value.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
        }
        else {
            key = line;
            value = "";
        }
        key.erase(key.find_last_not_of(" \t") + 1);
        key.erase(0, key.find_first_not_of(" \t"));
        blocks.push_back(std::make_pair(key, value));
    }
    for (const auto &block : blocks) {
        std::cout << block.first << " " << block.second << std::endl;
    }
}

Tokenizer::~Tokenizer() {}