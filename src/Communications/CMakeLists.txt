set(SOURCES
    ZMQContextManager.cpp
    ZMQRequest.cpp
    ZMQReceive.cpp
)

add_library(${ZMQ_COMMS_LIB} ${SOURCES})

target_include_directories(${ZMQ_COMMS_LIB} PUBLIC inc)

target_link_libraries(${ZMQ_COMMS_LIB} PUBLIC ${LOGGER_LIB} cppzmq)
