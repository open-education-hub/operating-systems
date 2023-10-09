add_library(connection connection.c)
target_link_libraries(connection utils log sock_util)

add_library(task task.c)
target_link_libraries(task utils log sock_util)

link_libraries(utils log sock_util connection task)

add_executable(fibo-server server.c)
set_property(TARGET fibo-server PROPERTY OUTPUT_NAME server)

add_executable(mt_server mt_server.c)
target_link_libraries(mt_server PRIVATE Threads::Threads)

add_executable(mp_server mp_server.c)

add_executable(mt_pool_server mt_pool_server.c)
target_link_libraries(mt_pool_server PRIVATE Threads::Threads)

add_executable(mp_pool_server mp_pool_server.c)
target_link_libraries(mp_pool_server PRIVATE Threads::Threads)

add_executable(mp_pool_server_works mp_pool_server_works.c)