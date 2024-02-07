add_library(webserv_internal STATIC
        hello/hello.cpp
        hello/hello.hpp
        config/config.cpp
        config/config.hpp
        config/route_config.cpp
        config/route_config.hpp
        http/method.hpp
        config/virtual_server_config.cpp
        config/virtual_server_config.hpp
        http/status.hpp
        http/status.cpp
        utils/utils.hpp)
