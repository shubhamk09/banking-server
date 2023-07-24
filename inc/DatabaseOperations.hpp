/**
 * @file DatabaseOperations.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <sqlite3.h>
#include <vector>
#include "Connection.hpp"

namespace Banking
{

class DatabaseOperations
{
private: 
    connection_shptr connPtr;
public:
    DatabaseOperations(connection_shptr &connPtr);
    ~DatabaseOperations() = default;
        
    DatabaseOperations(const DatabaseOperations&) = default;
    DatabaseOperations& operator=(const DatabaseOperations&) = default;
    DatabaseOperations(DatabaseOperations&&) = default;
    DatabaseOperations& operator=(DatabaseOperations&&) = default;
public:
    std::string getEmployeeNameById(std::string &empId);
    static int callbackName(void* data, int column_count, char** column_values, char** column_names);
};
    
} // namespace Banking