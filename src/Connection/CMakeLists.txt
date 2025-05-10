set(SOURCES
    Connection.cpp
)

add_library(${CONNECTION_LIB} ${SOURCES})

target_include_directories(${CONNECTION_LIB} PUBLIC inc)

target_link_libraries(${CONNECTION_LIB} PUBLIC ${LOGGER_LIB} ${SQLite3_LIB} ${ZMQ_COMMS_LIB} nlohmann_json::nlohmann_json)



# Need to remove the ${CONNECTION_LIB} from the other executable