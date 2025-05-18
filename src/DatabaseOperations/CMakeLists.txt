set(SOURCES
    DatabaseOperations.cpp
    EmployeeOperations.cpp
    CustomerOperations.cpp
    BranchOperations.cpp
    AccountOperations.cpp
    Dispatcher.cpp
)

add_library(${DATABASE_OPERATIONS_LIB} ${SOURCES})

target_include_directories(${DATABASE_OPERATIONS_LIB} PUBLIC inc)

target_link_libraries(${DATABASE_OPERATIONS_LIB} PUBLIC ${ZMQ_COMMS_LIB} ${LOGGER_LIB} ${USERS_LIB} nlohmann_json::nlohmann_json)



add_executable(${DATABASE_OPERATIONS_SERVICE} 
                Main.cpp)

target_link_libraries(${DATABASE_OPERATIONS_SERVICE} ${DATABASE_OPERATIONS_LIB} ${LOGGER_LIB} ${ZMQ_COMMS_LIB} nlohmann_json::nlohmann_json)