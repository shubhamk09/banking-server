#pragma once

#include "DatabaseOperations.hpp"
#include <gmock/gmock.h>

namespace Banking {
namespace Testing {

class MockDatabaseOperations : public IDatabaseOperations {
public:
    MOCK_METHOD(std::vector<std::string>, buildSelectionQuery, 
        (const std::string &colName, const std::string &searchVal, const std::string &tableName), (override));
    MOCK_METHOD(std::vector<std::string>, buildSelectionQuery, 
        (const std::string &colName, const std::string &searchVal, const std::string &tableName, const std::string &searchOn), (override));
    MOCK_METHOD(bool, buildUpdateQuery, 
        (const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName), (override));
    MOCK_METHOD(bool, buildUpdateQuery, 
        (const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName, const std::string &searchOn), (override));
    MOCK_METHOD(bool, buildInsertionQery, (const nlohmann::json &data), (override));
    MOCK_METHOD(bool, buildDeleteQuery, 
        (const std::string &searchVal, const std::string &tableName, const std::string &searchOn), (override));
    MOCK_METHOD(bool, SendQuery, 
        (const std::string &query, std::vector<std::string>* container), (override));
};

} // namespace Testing
} // namespace Banking
