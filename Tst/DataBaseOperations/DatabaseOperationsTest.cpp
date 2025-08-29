#include "DatabaseOperations.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nlohmann/json.hpp>
#include "../Mocks/MockZMQRequest.hpp"
#include "Logger.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::StrictMock;

// ================= DatabaseOperations Tests =================
class DatabaseOperationsTest : public ::testing::Test {
protected:
    void SetUp() override {
        Banking::Logger::Init();
        mockZMQRequest = std::make_unique<StrictMock<Banking::Testing::MockZMQRequest>>();
        dbOps = std::make_unique<Banking::DatabaseOperations>(*mockZMQRequest);
    }

    void TearDown() override {
        dbOps.reset();
        mockZMQRequest.reset();
    }

    std::unique_ptr<StrictMock<Banking::Testing::MockZMQRequest>> mockZMQRequest;
    std::unique_ptr<Banking::DatabaseOperations> dbOps;
};

// ================= buildSelectionQuery Tests =================

TEST_F(DatabaseOperationsTest, BuildSelectionQuery_ThreeParameters) {
    std::string expectedQuery = "SELECT Customer_name from Customer WHERE Customer_id = 'MYSC00001'";
    nlohmann::json mockResponse = {
        {"status", "success"},
        {"data", {"John Doe", "Jane Smith"}}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    std::vector<std::string> result = dbOps->buildSelectionQuery("Customer_name", "MYSC00001", "Customer");
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "\"John Doe\"");
    EXPECT_EQ(result[1], "\"Jane Smith\"");
}

TEST_F(DatabaseOperationsTest, BuildSelectionQuery_FourParameters) {
    std::string expectedQuery = "SELECT Branch_id from EmployeeToBranch WHERE Employee_id = 'MYSE00001'";
    nlohmann::json mockResponse = {
        {"status", "success"},
        {"data", {"MYS001"}}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    std::vector<std::string> result = dbOps->buildSelectionQuery("Branch_id", "MYSE00001", "EmployeeToBranch", "Employee_id");
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "\"MYS001\"");
}

TEST_F(DatabaseOperationsTest, BuildSelectionQuery_ErrorResponse) {
    std::string expectedQuery = "SELECT Customer_name from Customer WHERE Customer_id = 'INVALID'";
    nlohmann::json mockResponse = {
        {"status", "error"},
        {"message", "Customer not found"},
        {"data", nlohmann::json::array()}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    std::vector<std::string> result = dbOps->buildSelectionQuery("Customer_name", "INVALID", "Customer");
    
    EXPECT_TRUE(result.empty());
}

TEST_F(DatabaseOperationsTest, BuildSelectionQuery_EmptyDataArray) {
    std::string expectedQuery = "SELECT Customer_name from Customer WHERE Customer_id = 'MYSC00999'";
    nlohmann::json mockResponse = {
        {"status", "success"},
        {"data", nlohmann::json::array()}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    std::vector<std::string> result = dbOps->buildSelectionQuery("Customer_name", "MYSC00999", "Customer");
    
    EXPECT_TRUE(result.empty());
}

// ================= buildUpdateQuery Tests =================

TEST_F(DatabaseOperationsTest, BuildUpdateQuery_ThreeParameters) {
    std::string expectedQuery = "UPDATE Customer SET Customer_name = 'John Updated' WHERE Customer_id = 'MYSC00001'";
    nlohmann::json mockResponse = {
        {"status", "success"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->buildUpdateQuery("Customer_name", "MYSC00001", "John Updated", "Customer");
    
    EXPECT_TRUE(result);
}

TEST_F(DatabaseOperationsTest, BuildUpdateQuery_FourParameters) {
    std::string expectedQuery = "UPDATE Employee SET Employee_designation = 'Manager' WHERE Employee_id = 'MYSE00001'";
    nlohmann::json mockResponse = {
        {"status", "success"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->buildUpdateQuery("Employee_designation", "MYSE00001", "Manager", "Employee", "Employee_id");
    
    EXPECT_TRUE(result);
}

TEST_F(DatabaseOperationsTest, BuildUpdateQuery_ErrorResponse) {
    std::string expectedQuery = "UPDATE Customer SET Customer_name = 'Invalid Update' WHERE Customer_id = 'INVALID'";
    nlohmann::json mockResponse = {
        {"status", "error"},
        {"message", "Update failed"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->buildUpdateQuery("Customer_name", "INVALID", "Invalid Update", "Customer");
    
    EXPECT_FALSE(result);
}

// ================= buildInsertionQuery Tests =================

TEST_F(DatabaseOperationsTest, BuildInsertionQuery_ValidData) {
    nlohmann::json insertData = {
        {"table", "Customer"},
        {"values", {"MYSC00999", "New Customer", "password123", "MYS001", "New Address", "ACC12345"}}
    };
    
    std::string expectedQuery = "INSERT INTO 'Customer' VALUES (\"MYSC00999\", \"New Customer\", \"password123\", \"MYS001\", \"New Address\", \"ACC12345\");";
    nlohmann::json mockResponse = {
        {"status", "success"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->buildInsertionQery(insertData);
    
    EXPECT_TRUE(result);
}

TEST_F(DatabaseOperationsTest, BuildInsertionQuery_SingleValue) {
    nlohmann::json insertData = {
        {"table", "Branch"},
        {"values", {"MYS999"}}
    };
    
    std::string expectedQuery = "INSERT INTO 'Branch' VALUES (\"MYS999\");";
    nlohmann::json mockResponse = {
        {"status", "success"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->buildInsertionQery(insertData);
    
    EXPECT_TRUE(result);
}

TEST_F(DatabaseOperationsTest, BuildInsertionQuery_NonArrayValues) {
    nlohmann::json insertData = {
        {"table", "Customer"},
        {"values", "not an array"}
    };
    
    // Should not make any ZMQ request since values is not an array
    // EXPECT_CALL is intentionally omitted - no request should be made
    
    bool result = dbOps->buildInsertionQery(insertData);
    
    EXPECT_FALSE(result);
}

TEST_F(DatabaseOperationsTest, BuildInsertionQuery_ErrorResponse) {
    nlohmann::json insertData = {
        {"table", "Customer"},
        {"values", {"DUPLICATE_ID", "Customer"}}
    };
    
    std::string expectedQuery = "INSERT INTO 'Customer' VALUES (\"DUPLICATE_ID\", \"Customer\");";
    nlohmann::json mockResponse = {
        {"status", "error"},
        {"message", "Duplicate key"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->buildInsertionQery(insertData);
    
    EXPECT_FALSE(result);
}

// ================= buildDeleteQuery Tests =================

TEST_F(DatabaseOperationsTest, BuildDeleteQuery_Success) {
    std::string expectedQuery = "DELETE FROM Customer WHERE Customer_id = 'MYSC00001'";
    nlohmann::json mockResponse = {
        {"status", "success"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->buildDeleteQuery("MYSC00001", "Customer", "Customer_id");
    
    EXPECT_TRUE(result);
}

TEST_F(DatabaseOperationsTest, BuildDeleteQuery_ErrorResponse) {
    std::string expectedQuery = "DELETE FROM Customer WHERE Customer_id = 'NONEXISTENT'";
    nlohmann::json mockResponse = {
        {"status", "error"},
        {"message", "Record not found"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(expectedQuery))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->buildDeleteQuery("NONEXISTENT", "Customer", "Customer_id");
    
    EXPECT_FALSE(result);
}

// ================= SendQuery Tests =================

TEST_F(DatabaseOperationsTest, SendQuery_SelectWithContainer) {
    std::string query = "SELECT Customer_name from Customer WHERE Customer_id = 'MYSC00001'";
    nlohmann::json mockResponse = {
        {"status", "success"},
        {"data", {"John Doe", "Jane Smith"}}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(query))
        .WillOnce(Return(mockResponse.dump()));
    
    std::vector<std::string> container;
    bool result = dbOps->SendQuery(query, &container);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], "\"John Doe\"");
    EXPECT_EQ(container[1], "\"Jane Smith\"");
}

TEST_F(DatabaseOperationsTest, SendQuery_NonSelectOperation) {
    std::string query = "UPDATE Customer SET Customer_name = 'Updated' WHERE Customer_id = 'MYSC00001'";
    nlohmann::json mockResponse = {
        {"status", "success"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(query))
        .WillOnce(Return(mockResponse.dump()));
    
    bool result = dbOps->SendQuery(query);
    
    EXPECT_TRUE(result);
}

TEST_F(DatabaseOperationsTest, SendQuery_ErrorStatus) {
    std::string query = "SELECT * FROM NonExistentTable";
    nlohmann::json mockResponse = {
        {"status", "error"},
        {"message", "Table does not exist"}
    };
    
    EXPECT_CALL(*mockZMQRequest, request(query))
        .WillOnce(Return(mockResponse.dump()));
    
    std::vector<std::string> container;
    bool result = dbOps->SendQuery(query, &container);
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(container.empty());
}

// ================= Constructor Tests =================

TEST(DatabaseOperationsConstructorTest, DefaultConstructor) {
    Banking::Logger::Init();
    
    // Test that default constructor doesn't crash
    EXPECT_NO_THROW({
        Banking::DatabaseOperations dbOps;
    });
}

TEST(DatabaseOperationsConstructorTest, ConstructorWithZMQRequest) {
    Banking::Logger::Init();
    StrictMock<Banking::Testing::MockZMQRequest> mockRequest;
    
    EXPECT_NO_THROW({
        Banking::DatabaseOperations dbOps(mockRequest);
    });
}
