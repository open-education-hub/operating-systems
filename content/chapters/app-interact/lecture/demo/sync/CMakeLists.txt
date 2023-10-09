link_libraries(Threads::Threads utils)

add_executable(thread_sem_sync thread_sem.c)
set_property(TARGET thread_sem_sync PROPERTY OUTPUT_NAME thread_sem)

add_executable(thread_cond thread_cond.c)
add_executable(proc_sem_first proc_sem_first.c)
add_executable(proc_sem_second proc_sem_second.c)
add_executable(proc_sig_first proc_sig_first.c)
add_executable(proc_sig_second proc_sig_second.c)
