/**
 * @file DatabaseOperations.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BANKING_DATABASEOPERATION_HPP
#define BANKING_DATABASEOPERATION_HPP

#include <vector>
#include "Logger.hpp"
#include <nlohmann/json.hpp>

namespace Banking
{

class DatabaseOperations
{
public:
    DatabaseOperations();
    virtual ~DatabaseOperations() = default;
        
    DatabaseOperations(const DatabaseOperations&) = default;
    DatabaseOperations& operator=(const DatabaseOperations&) = default;
    DatabaseOperations(DatabaseOperations&&) = default;
    DatabaseOperations& operator=(DatabaseOperations&&) = default;
public:

    static std::vector<std::string> buildSelectionQuery(const std::string &colName, const std::string &searchVal, const std::string &tableName);
    static std::vector<std::string> buildSelectionQuery(const std::string &colName, const std::string &searchVal, const std::string &tableName, const std::string &seearchOn);
    static bool buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName);
    static bool buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName, const std::string &seearchOn);
    static bool buildInsertionQery(const nlohmann::json &data);
    static bool buildDeleteQuery(const std::string &searchVal, const std::string &tableName, const std::string &seearchOn);
    // static int callbackName(void* data, int column_count, char** column_values, char** column_names);
    static bool SendQuery(const std::string &query, std::vector<std::string>* container = nullptr);
};

using dbOperation_shptr = std::shared_ptr<DatabaseOperations>;
    
} // namespace Banking

#endif //BANKING_DATABASEOPERATION_HPP