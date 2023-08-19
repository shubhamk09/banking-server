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
#ifndef BANKING_DATABASEOPERATION_HPP
#define BANKING_DATABASEOPERATION_HPP

#include <sqlite3.h>
#include <vector>
#include "Connection.hpp"
#include "Logger.hpp"

namespace Banking
{

class DatabaseOperations
{
protected: 
    connection_shptr connPtr;
public:
    DatabaseOperations(connection_shptr &connPtr);
    virtual ~DatabaseOperations() = default;
        
    DatabaseOperations(const DatabaseOperations&) = default;
    DatabaseOperations& operator=(const DatabaseOperations&) = default;
    DatabaseOperations(DatabaseOperations&&) = default;
    DatabaseOperations& operator=(DatabaseOperations&&) = default;
public:

    std::string buildSelectionQuery(std::string &colName, std::string &searchVal, std::string &tableName);
    std::string buildSelectionQuery(std::string &colName, std::string &searchVal, std::string &tableName, std::string &seearchOn);
    static int callbackName(void* data, int column_count, char** column_values, char** column_names);
};

using dbOperation_shptr = std::shared_ptr<DatabaseOperations>;
    
} // namespace Banking

#endif //BANKING_DATABASEOPERATION_HPP