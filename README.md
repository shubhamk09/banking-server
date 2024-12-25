# banking-server
 Server for Banking application

# Compile with coverage support
gcc -fprofile-arcs -ftest-coverage -o my_program my_program.c

# Run tests
./my_program

# Capture coverage data
lcov --capture --directory . --output-file coverage.info

# Filter out external libraries and system headers
lcov --remove coverage.info '/usr/*' --output-file coverage.filtered.info

# Generate HTML report
genhtml --output-directory out coverage.filtered.info

# Print a var in cmake
include(CMakePrintHelpers)
cmake_print_variables(PROJECT_SOURCE_DIR)


 [![MSYS2](https://github.com/shubhamk09/banking-server/actions/workflows/main.yml/badge.svg)](https://github.com/shubhamk09/banking-server/actions/workflows/main.yml)
 [![Ubuntu-Build](https://github.com/shubhamk09/banking-server/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/shubhamk09/banking-server/actions/workflows/cmake-single-platform.yml)
 [![Coverage](https://github.com/shubhamk09/banking-server/actions/workflows/Code-Coverage.yml/badge.svg)](https://github.com/shubhamk09/banking-server/actions/workflows/Code-Coverage.yml)
