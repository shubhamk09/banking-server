# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.26)

# Set C++ standard to C++ 17
set(CMAKE_CXX_STANDARD 17)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(
  ModernCMakeExample
  VERSION 1.0
  LANGUAGES CXX)

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

# Find packages go here.
include(${CMAKE_CURRENT_SOURCE_DIR}/Cmake/LibList.cmake)
# You should usually split this into folders, but this is a simple example
add_subdirectory(src)
# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system

# Link each target with other targets or add options, etc.

# Adding something we can run - Output name matches target name
add_executable(BankingServer driver.cpp)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_link_libraries(BankingServer PRIVATE ${USERS_LIB} ${CONNECTION_LIB} ${DATABASE_OPERATIONS_LIB} ${LOGGER_LIB} spdlog nlohmann_json::nlohmann_json)
