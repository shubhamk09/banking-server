set(SOURCES
    Connection.cpp
)

add_library(${CONNECTION_LIB} ${SOURCES})

target_include_directories(${CONNECTION_LIB} PUBLIC inc)

target_link_libraries(${CONNECTION_LIB} PUBLIC libsqlite3)
