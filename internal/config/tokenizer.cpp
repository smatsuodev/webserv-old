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

bool    server_block_start(const std::string &line) {
    if (line == "[[server]]") {
        return true;
    }
    return false;
}

bool    route_block_start(const std::string &line) {
    if (line == "[[server.route]]") {
        return true;
    }
    return false;
}

std::vector<std::pair<std::string, std::string> > get_server_block(const std::vector<std::string> &input, size_t *i) {
    std::vector<std::pair<std::string, std::string> > server_block;
    for (size_t j = *i + 1; j < input.size(); j++) {
        if (input[j].find("[[") == 0 || input[j].empty()) {
            *i = j;
            return server_block;
        }
        size_t pos = input[j].find('=');
        if (pos != std::string::npos) {
            std::string key = input[j].substr(0, pos);
            key.erase(key.find_last_not_of(" \t") + 1);
            key.erase(0, key.find_first_not_of(" \t"));
            std::string value = input[j].substr(pos + 1);
            value.erase(value.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            server_block.push_back(std::make_pair(key, value));
        }
    }
    *i = input.size();
    return server_block;
}

std::pair<std::string, std::string> get_common_block(const std::string &line) {
    std::pair<std::string, std::string> common_block;
    size_t pos = line.find('=');
    if (pos != std::string::npos) {
        std::string key = line.substr(0, pos);
        key.erase(key.find_last_not_of(" \t") + 1);
        key.erase(0, key.find_first_not_of(" \t"));
        std::string value = line.substr(pos + 1);
        value.erase(value.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        common_block = std::make_pair(key, value);
    }
    return common_block;
}

void validateBlocks(bool server_block, bool route_block, bool common_block) {
    if (!server_block) {
        throw std::runtime_error("No server block");
    }
    if (!route_block) {
        throw std::runtime_error("No route block");
    }
    if (!common_block) {
        throw std::runtime_error("No common block");
    }
}

void    print_config(const std::vector<std::pair<std::string, std::string> > &server_config_blocks,
                     const std::vector<std::vector<std::pair<std::string, std::string> > > &route_config_blocks,
                     const std::vector<std::pair<std::string, std::string> > &common_config_blocks) {
    std::cout << "Server config:" << std::endl;
    for (size_t i = 0; i < server_config_blocks.size(); i++) {
        std::cout << "\t[" << server_config_blocks[i].first << "] = [" << server_config_blocks[i].second << "]" << std::endl;
    }
    std::cout << "Route config:" << std::endl;
    for (size_t i = 0; i < route_config_blocks.size(); i++) {
        std::cout << "\tRoute " << i << ":" << std::endl;
        for (size_t j = 0; j < route_config_blocks[i].size(); j++) {
            std::cout << "\t\t[" << route_config_blocks[i][j].first << "] = [" << route_config_blocks[i][j].second << "]" << std::endl;
        }
    }
    std::cout << "Common config:" << std::endl;
    for (size_t i = 0; i < common_config_blocks.size(); i++) {
        std::cout << "\t[" << common_config_blocks[i].first << "] = [" << common_config_blocks[i].second << "]" << std::endl;
    }
}

Tokenizer::Tokenizer(const std::string &path) {
    std::vector<std::string> input = getConfString(path);
    bool server_block = false;
    bool route_block = false;
    bool common_block = false;

    for (size_t i = 0; i < input.size(); i++) {
        std::string line = input[i];
        if (line.empty() || std::all_of(line.begin(), line.end(), isspace))
            continue ;
        if (server_block_start(line)) {
            if (server_block) {
                throw std::runtime_error("Invalid server block");
            }
            server_block = true;
            server_config_blocks_ = get_server_block(input, &i);
        }
        else if (route_block_start(line)) {
            route_block = true;
            route_config_blocks_.push_back(get_server_block(input, &i));
        }
        else {
            common_block = true;
            common_config_blocks_.push_back(get_common_block(line));
        }
    }
    validateBlocks(server_block, route_block, common_block);
    print_config(server_config_blocks_, route_config_blocks_, common_config_blocks_);
}

Tokenizer::~Tokenizer() {}