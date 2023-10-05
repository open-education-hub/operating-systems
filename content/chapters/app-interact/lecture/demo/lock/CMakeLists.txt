link_libraries(utils Threads::Threads)

add_executable(thread_mutex thread_mutex.c)
add_executable(thread_sem thread_sem.c)
add_executable(proc_sem proc_sem.c)
add_executable(proc_flock proc_flock.c)
