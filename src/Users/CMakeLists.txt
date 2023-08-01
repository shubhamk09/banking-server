set(SOURCES
        User.cpp
        Employee.cpp
)

add_library(${USERS_LIB} ${SOURCES})

target_include_directories(${USERS_LIB} PUBLIC inc)

