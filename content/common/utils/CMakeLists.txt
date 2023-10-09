add_library(utils INTERFACE)

target_include_directories(utils INTERFACE include)

target_link_libraries(utils INTERFACE log)

add_subdirectory(log)
add_subdirectory(sock)
