include(${CMAKE_CURRENT_SOURCE_DIR}/../../Cmake/LibList.cmake)

# Test executable name
set(CONNECTION_TEST connection_test)

# Add the test executable
add_executable(${CONNECTION_TEST}
    ConnectionTest.cpp
)

# Link libraries to the test executable
target_link_libraries(${CONNECTION_TEST} 
    PRIVATE 
    gtest_main
    gmock_main
    ${CONNECTION_LIB}
    ${LOGGER_LIB}
    ${PLATFORM_LIBS}
)

# Add the test to CTest
add_test(NAME ${CONNECTION_TEST} COMMAND ${CONNECTION_TEST})
