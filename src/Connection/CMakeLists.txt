set(SOURCES
    Connection.cpp
)

add_library(${CONNECTION_LIB} ${SOURCES})

target_include_directories(${CONNECTION_LIB} PUBLIC inc)

target_link_libraries(${CONNECTION_LIB} PUBLIC ${LOGGER_LIB} ${ZMQ_COMMS_LIB} ${SQLite3_LIB} ${ZMQ_COMMS_LIB} nlohmann_json::nlohmann_json)

add_executable(${CONNECTION_SERVICE} 
                Main.cpp)

target_link_libraries(${CONNECTION_SERVICE} ${CONNECTION_LIB} ${LOGGER_LIB} ${ZMQ_COMMS_LIB} nlohmann_json::nlohmann_json)