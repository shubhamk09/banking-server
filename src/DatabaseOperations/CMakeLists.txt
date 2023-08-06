set(SOURCES
    DatabaseOperations.cpp
    EmployeeOperations.cpp
    CustomerOperations.cpp
)

add_library(${DATABASE_OPERATIONS_LIB} ${SOURCES})

target_include_directories(${DATABASE_OPERATIONS_LIB} PUBLIC inc)

target_link_libraries(${DATABASE_OPERATIONS_LIB} PUBLIC ${CONNECTION_LIB})
