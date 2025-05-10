# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.26)

# Set C++ standard to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This is your project statement
project(
  ModernCMakeExample
  VERSION 1.0
  LANGUAGES CXX
)

set(CTEST_BINARY_DIRECTORY build)

# Enable coverage flags for GCC and Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

# Detect Windows (MinGW or MSVC) vs. Linux
if (WIN32)
    message(STATUS "Detected Windows")
    add_definitions(-D_WIN32)
    
    if (MINGW)
        message(STATUS "Using MinGW")
        add_definitions(-DUSING_MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static-libgcc -static-libstdc++")
    elseif (MSVC)
        message(STATUS "Using MSVC")
        add_definitions(-DUSING_MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
    endif()
    
    # Windows-specific libraries
    set(PLATFORM_LIBS ws2_32)

elseif (UNIX)
    message(STATUS "Detected Linux")
    add_definitions(-DUSING_LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")
    
    # Linux-specific libraries
    set(PLATFORM_LIBS pthread)
endif()

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

# Find packages go here.
# Include packages
include(CTest)
include(CTestCoverageCollectGCOV)
include(${CMAKE_CURRENT_SOURCE_DIR}/Cmake/LibList.cmake)

# You should usually split this into folders, but this is a simple example
add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(Tst)

  # Define a list of all test targets
  # set(TEST_TARGETS
  # ${ZMQCOMMS_TEST}
  # ${DATABASE_OPERATIONS_TEST}
  # ${USERS_TEST}
  # )
    # Apply the UNIT_TEST definition to all test targets
  # foreach(TEST_TARGET ${TEST_TARGETS})
  #   target_compile_definitions(${TEST_TARGET} PRIVATE UNIT_TEST)
  # endforeach()

endif()
# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system

message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")

# Add custom target to collect coverage data
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(COVERAGE_INFO "${CMAKE_BINARY_DIR}/coverage.info")
    set(COVERAGE_REPORT_DIR "${CMAKE_BINARY_DIR}/coverage_report")
    add_custom_target(coverage
        COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info
        COMMAND lcov --remove ${CMAKE_BINARY_DIR}/coverage.info '/usr/*' --output-file ${CMAKE_BINARY_DIR}/coverage.info
        COMMAND genhtml ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage_report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating code coverage report")
endif()

include(CMakePrintHelpers)
cmake_print_variables(PROJECT_SOURCE_DIR)
cmake_print_variables(CMAKE_BINARY_DIR)
cmake_print_variables(CMAKE_SOURCE_DIR)

# Adding something we can run - Output name matches target name
# add_executable(BankingServer driver.cpp)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
# target_link_libraries(BankingServer PRIVATE ${USERS_LIB} ${CONNECTION_LIB} ${DATABASE_OPERATIONS_LIB} ${LOGGER_LIB} spdlog nlohmann_json::nlohmann_json libzmq ${PLATFORM_LIBS})

# Run lcov
# lcov --capture --directory . --output-file coverage.info
# genhtml coverage.info --output-directory out
# Exclude an unwanted folder
# lcov --remove coverage.info '/usr/*' --output-file coverage_filtered.info
# Combined coverage
# lcov -a coverage1.info -a coverage2.info -o combined_coverage.info
