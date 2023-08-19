set(SOURCES
        Logger.cpp
)

add_library(${LOGGER_LIB} ${SOURCES})

target_include_directories(${LOGGER_LIB} PUBLIC inc)

target_link_libraries(${LOGGER_LIB} PUBLIC spdlog)

