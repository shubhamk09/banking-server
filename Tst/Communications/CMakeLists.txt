set(ZMQCOMMS_TEST zmqcomms_test)
add_executable(${ZMQCOMMS_TEST} ZMQCommsTest.cpp ZMQReceiveTest.cpp ZMQSocketTest.cpp)
target_link_libraries(${ZMQCOMMS_TEST} ${ZMQ_COMMS_LIB} gtest gmock gtest_main pthread MockZMQSocket)

add_test(NAME ${ZMQCOMMS_TEST} COMMAND ${ZMQCOMMS_TEST})

# Socket tests
set(SOCKET_TEST socket_test)
add_executable(${SOCKET_TEST} SocketTest.cpp)
target_link_libraries(${SOCKET_TEST} socket-comms-lib logger-lib gtest gmock gtest_main pthread)

add_test(NAME ${SOCKET_TEST} COMMAND ${SOCKET_TEST})

