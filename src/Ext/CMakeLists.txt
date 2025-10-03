set(ZMQ_BUILD_TESTS OFF)
set(ENABLE_CPACK OFF)
set(CPPZMQ_BUILD_TESTS OFF)

add_subdirectory(json-develop)
add_subdirectory(spdlog-1.x)
add_subdirectory(sqlite3)
add_subdirectory(libzmq)
add_subdirectory(cppzmq)


