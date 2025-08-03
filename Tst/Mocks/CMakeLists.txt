# CMakeLists.txt for Mocks
add_library(MockZMQSocket STATIC MockZMQSocket.cpp)
target_include_directories(MockZMQSocket PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(MockZMQSocket gmock ${ZMQ_COMMS_LIB})

# Add MockDatabaseOperations as a header-only library
add_library(MockDatabaseOperations INTERFACE)
target_link_libraries(MockDatabaseOperations 
    INTERFACE 
    ${DATABASE_OPERATIONS_LIB}
    gmock)
