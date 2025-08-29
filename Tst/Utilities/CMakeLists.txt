include(${CMAKE_CURRENT_SOURCE_DIR}/../../Cmake/LibList.cmake)

# Test executable name
set(LOGGER_TEST logger_test)

# Add the test executable
add_executable(${LOGGER_TEST}
    LoggerTest.cpp
)

# Link libraries to the test executable
target_link_libraries(${LOGGER_TEST} 
    PRIVATE 
    gtest_main
    gmock_main
    ${LOGGER_LIB}
    ${PLATFORM_LIBS}
)

# Add the test to CTest
add_test(NAME ${LOGGER_TEST} COMMAND ${LOGGER_TEST})
