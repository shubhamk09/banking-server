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
#include <memory>
#include "Logger.hpp"
#include "ZMQRequest.hpp"
#include <nlohmann/json.hpp>

namespace Banking
{

class IDatabaseOperations {
public:
    virtual ~IDatabaseOperations() = default;
    
    virtual std::vector<std::string> buildSelectionQuery(const std::string &colName, const std::string &searchVal, const std::string &tableName) = 0;
    virtual std::vector<std::string> buildSelectionQuery(const std::string &colName, const std::string &searchVal, const std::string &tableName, const std::string &searchOn) = 0;
    virtual bool buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName) = 0;
    virtual bool buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName, const std::string &searchOn) = 0;
    virtual bool buildInsertionQery(const nlohmann::json &data) = 0;
    virtual bool buildDeleteQuery(const std::string &searchVal, const std::string &tableName, const std::string &searchOn) = 0;
    virtual bool SendQuery(const std::string &query, std::vector<std::string>* container = nullptr) = 0;
};

class DatabaseOperations : public IDatabaseOperations
{
private:
    ZMQRequest& zmqRequestor;

public:
    DatabaseOperations();
    explicit DatabaseOperations(ZMQRequest& requestor);
    virtual ~DatabaseOperations() = default;
    
    DatabaseOperations(const DatabaseOperations&) = delete;
    DatabaseOperations& operator=(const DatabaseOperations&) = delete;
    DatabaseOperations(DatabaseOperations&&) = default;
    DatabaseOperations& operator=(DatabaseOperations&&) = default;

    std::vector<std::string> buildSelectionQuery(const std::string &colName, const std::string &searchVal, const std::string &tableName) override;
    std::vector<std::string> buildSelectionQuery(const std::string &colName, const std::string &searchVal, const std::string &tableName, const std::string &searchOn) override;
    bool buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName) override;
    bool buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName, const std::string &searchOn) override;
    bool buildInsertionQery(const nlohmann::json &data) override;
    bool buildDeleteQuery(const std::string &searchVal, const std::string &tableName, const std::string &searchOn) override;
    bool SendQuery(const std::string &query, std::vector<std::string>* container = nullptr) override;
};

using dbOperation_shptr = std::shared_ptr<DatabaseOperations>;
    
} // namespace Banking

#endif //BANKING_DATABASEOPERATION_HPP