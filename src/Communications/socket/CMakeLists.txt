set(LIB_SOURCES
    TcpSocket.cpp
    TcpServer.cpp
    TcpClient.cpp
)

# Library
add_library(${SOCKET_COMMS_LIB} ${LIB_SOURCES})

target_include_directories(${SOCKET_COMMS_LIB} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/src/Ext/asio/asio/include
)

target_link_libraries(${SOCKET_COMMS_LIB} PUBLIC ${LOGGER_LIB})

# Server executable
add_executable(socket_server ServerMain.cpp)
target_link_libraries(socket_server PRIVATE ${SOCKET_COMMS_LIB} ${ZMQ_COMMS_LIB})

# Client executable
add_executable(socket_client ClientMain.cpp)
target_link_libraries(socket_client PRIVATE ${SOCKET_COMMS_LIB} ${ZMQ_COMMS_LIB})
