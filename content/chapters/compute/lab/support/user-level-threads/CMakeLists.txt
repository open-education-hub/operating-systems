cmake_minimum_required(VERSION 3.13)

project(user_level_threads C CXX)

# LIBBOOST
set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED COMPONENTS context fiber)
find_package(Threads REQUIRED)

include_directories(PUBLIC ${Boost_INCLUDE_DIRS})
link_libraries(Boost::context)
link_libraries(Boost::fiber)
link_libraries(Threads::Threads)
add_compile_definitions(PUBLIC BOOST_STACKTRACE_USE_ADDR2LINE)

add_executable(simple simple.cc)
add_executable(sum sum.cc)
add_executable(yield_launch yield_launch.cc)
add_executable(yield_barrier yield_barrier.cc)
add_executable(threads_and_fibers threads_and_fibers.cc)
