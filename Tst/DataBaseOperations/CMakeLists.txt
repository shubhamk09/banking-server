set(DATABASE_OPERATIONS_TEST database_operations_test)
add_executable(${DATABASE_OPERATIONS_TEST} 
                EmployeeOperationsTest.cpp 
                AccountOperationsTest.cpp
                BranchOperationsTest.cpp 
                CustomerOperationsTest.cpp
                DatabaseOperationsTest.cpp)
target_link_libraries(${DATABASE_OPERATIONS_TEST} ${DATABASE_OPERATIONS_LIB} gtest gmock gtest_main MockDatabaseOperations MockZMQRequest pthread)

target_include_directories(${DATABASE_OPERATIONS_TEST} PRIVATE
                         ${CMAKE_SOURCE_DIR}/Tst/Mocks)
# target_include_directories(${DATABASE_OPERATIONS_TEST} PRIVATE
#                          ${CMAKE_SOURCE_DIR}/Tst/Mocks
#                          ${CMAKE_SOURCE_DIR}/src/DatabaseOperations/inc
#                          ${CMAKE_SOURCE_DIR}/src/Ext/json-develop/single_include
#                          ${CMAKE_SOURCE_DIR}/src/Logger/inc)

# target_link_libraries(${DATABASE_OPERATIONS_TEST} 
#                      ${DATABASE_OPERATIONS_LIB} 
#                      MockDatabaseOperations
#                      gmock 
#                      gmock_main
#                      gtest 
#                      gtest_main
#                      pthread)

add_test(NAME ${DATABASE_OPERATIONS_TEST} COMMAND ${DATABASE_OPERATIONS_TEST})

