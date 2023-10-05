add_executable(password-cracker-multiprocess password-cracker-multiprocess.c)

target_link_libraries(password-cracker-multiprocess PRIVATE
    OpenSSL::Crypto
    utils
    log
)

add_executable(password-cracker-multithread password-cracker-multithread.c)

target_compile_options(password-cracker-multithread PRIVATE
    -Wno-int-to-pointer-cast
    -Wno-pointer-to-int-cast
)

target_link_libraries(password-cracker-multithread PRIVATE
    Threads::Threads
    OpenSSL::Crypto
    utils
    log
)
