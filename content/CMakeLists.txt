cmake_minimum_required(VERSION 3.13)

project(so-content C CXX)

# crypto
find_package(OpenSSL REQUIRED)

# pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(chapters/app-interact)
add_subdirectory(chapters/compute)
add_subdirectory(chapters/data)
add_subdirectory(chapters/io)
add_subdirectory(chapters/software-stack)
add_subdirectory(common/utils)
