set(DATABASE_OPERATIONS_TEST database_operations_test)
add_executable(${DATABASE_OPERATIONS_TEST} EmployeeOperationsTest.cpp AccountOperationsTest.cpp)
target_link_libraries(${DATABASE_OPERATIONS_TEST} ${DATABASE_OPERATIONS_LIB} gtest gtest_main pthread)

add_test(NAME ${DATABASE_OPERATIONS_TEST} COMMAND ${DATABASE_OPERATIONS_TEST})

