# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.26)

# Set C++ standard to C++ 17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(
  ModernCMakeExample
  VERSION 1.0
  LANGUAGES CXX)

  
set(CTEST_BINARY_DIRECTORY build)

# Enable coverage flags for GCC and Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage)
    add_link_options(--coverage)
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
endif()
# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system


# Add coverage flags if using GCC or Clang
# if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     set(COVERAGE_FLAGS "-fprofile-arcs -ftest-coverage")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COVERAGE_FLAGS}")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
# endif()


# Link each target with other targets or add options, etc.

# Collect coverage data with gcov
# if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     enable_testing()
#     ctest_coverage_collect_gcov(
#         TARBALL gcov.tar  # Name of the output tar archive
#         SOURCE "${CMAKE_SOURCE_DIR}"
#         BINARY "${CMAKE_BINARY_DIR}"
#         OUTPUT_FILE "${CMAKE_BINARY_DIR}/coverage.info")
# endif()

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
add_executable(BankingServer driver.cpp)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_link_libraries(BankingServer PRIVATE ${USERS_LIB} ${CONNECTION_LIB} ${DATABASE_OPERATIONS_LIB} ${LOGGER_LIB} spdlog nlohmann_json::nlohmann_json)

# Run lcov
# lcov --capture --directory . --output-file coverage.info
# genhtml coverage.info --output-directory out
# Exclude a unwanted folder
# lcov --remove coverage.info '/usr/*' --output-file coverage_filtered.info
# combined coverage
# lcov -a coverage1.info -a coverage2.info -o combined_coverage.info
