add_library(sock_util sock_util.c)

target_include_directories(sock_util PUBLIC include)

target_link_libraries(sock_util PRIVATE utils)
