project(${SQLite3_LIB} VERSION 3.40.1 LANGUAGES C)

set(SOURCES
    shell.c
    sqlite3.c
)

add_library(${SQLite3_LIB} STATIC ${SOURCES})
target_include_directories(${SQLite3_LIB} PUBLIC inc)

