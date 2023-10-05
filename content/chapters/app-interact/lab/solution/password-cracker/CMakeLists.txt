add_executable(password-cracker-multiprocess-sol password-cracker-multiprocess.c)

target_link_libraries(password-cracker-multiprocess-sol PRIVATE
    OpenSSL::Crypto
    utils
    log
)
