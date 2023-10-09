link_libraries(utils log)

add_executable(signal_printer signal_printer.c)
add_executable(rt_signal_printer rt_signal_printer.c)
add_executable(signal_sender signal_sender.c)
add_executable(signal_sender_sleep signal_sender_sleep.c)
add_executable(rt_signal_sender rt_signal_sender.c)
