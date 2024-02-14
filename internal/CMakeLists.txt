add_library(webserv_internal STATIC
        config/config.cpp
        config/config.hpp
        config/route_config.cpp
        config/route_config.hpp
        http/method.hpp
        config/virtual_server_config.cpp
        config/virtual_server_config.hpp
        http/status.hpp
        http/status.cpp
        utils/utils.hpp
        http/request.cpp
        http/request.hpp
        utils/option.hpp
)
