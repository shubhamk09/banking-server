# set(SOURCES
#         Logger.cpp
# )

add_library(${LOGGER_LIB} INTERFACE)

target_include_directories(${LOGGER_LIB} INTERFACE inc)

target_link_libraries(${LOGGER_LIB} INTERFACE spdlog)

