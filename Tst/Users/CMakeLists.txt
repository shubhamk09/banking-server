set(USERS_TEST users_test)
add_executable(${USERS_TEST} EmployeeTest.cpp)
target_link_libraries(${USERS_TEST} ${USERS_LIB} gtest gtest_main pthread)

add_test(NAME ${USERS_TEST} COMMAND ${USERS_TEST})

