link_libraries(Threads::Threads utils rt)

add_executable(shmem_threads shmem_threads.c)

add_executable(shmem_file_reader shmem_reader.c)
target_compile_definitions(shmem_file_reader PUBLIC SHMEM_FILE)

add_executable(shmem_file_writer shmem_writer.c)
target_compile_definitions(shmem_file_writer PUBLIC SHMEM_FILE)

add_executable(shmem_shm_reader shmem_reader.c)
target_compile_definitions(shmem_shm_reader PUBLIC SHMEM_SHM)

add_executable(shmem_shm_writer shmem_writer.c)
target_compile_definitions(shmem_shm_writer PUBLIC SHMEM_SHM)
