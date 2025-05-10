set(ZMQCOMMS_TEST zmqcomms_test)
add_executable(${ZMQCOMMS_TEST} ZMQCommsTest.cpp)
target_link_libraries(${ZMQCOMMS_TEST} ${ZMQ_COMMS_LIB} gtest gmock gtest_main pthread)

add_test(NAME ${ZMQCOMMS_TEST} COMMAND ${ZMQCOMMS_TEST})

