// FILE: src/DatabaseOperations/inc/test_CustomerOperations.hpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CustomerOperations.hpp"
#include "Customer.hpp"
#include "MockDatabaseOperations.hpp"

namespace Banking {

class CustomerOperationsTest : public ::testing::Test {
protected:
    void SetUp() override {
        Banking::Logger::Init();
        mockDb = std::make_shared<testing::StrictMock<Banking::Testing::MockDatabaseOperations>>();
        customerOps = std::make_unique<CustomerOperations>(mockDb);
        customerId = "MYSC00102";
        
        // Setup mock expectations for addCustomer
        EXPECT_CALL(*mockDb, buildInsertionQery(testing::_))
            .WillOnce(testing::Return(true));
            
        Customer newCustomer(customerId, "John Doe", "password123", "MYS001", "123 Main St", "20230914MYS00104");
        customerOps->addCustomer(std::move(newCustomer));
    }

    void TearDown() override {
        // Setup mock expectation for deleteCustomer
        EXPECT_CALL(*mockDb, buildDeleteQuery(customerId, "Customer", "Customer_id"))
            .WillOnce(testing::Return(true));
            
        customerOps->deleteCustomer(customerId);
    }

    std::shared_ptr<testing::StrictMock<Banking::Testing::MockDatabaseOperations>> mockDb;
    std::unique_ptr<CustomerOperations> customerOps;
    std::string customerId;
};

TEST_F(CustomerOperationsTest, GetCustomerNameById) {
    std::string expectedName = "John Doe";
    
    std::vector<std::string> mockResult = {expectedName};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_name", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerNameById(customerId), expectedName);
}

TEST_F(CustomerOperationsTest, GetCustomerPasswordById) {
    std::string expectedPassword = "password123";
    
    std::vector<std::string> mockResult = {expectedPassword};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_password", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerPasswordById(customerId), expectedPassword);
}

TEST_F(CustomerOperationsTest, GetCustomerAccountById) {
    std::string expectedAccount = "20230914MYS00104";
    
    std::vector<std::string> mockResult = {expectedAccount};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_account", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerAccountById(customerId), expectedAccount);
}

TEST_F(CustomerOperationsTest, GetCustomerAddressById) {
    std::string expectedAddress = "123 Main St";
    
    std::vector<std::string> mockResult = {expectedAddress};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_address", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerAddressById(customerId), expectedAddress);
}

TEST_F(CustomerOperationsTest, GetCustomerBranchById) { 
    std::string expectedBranch = "MYS001";
    
    std::vector<std::string> mockResult = {expectedBranch};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_branch", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerBranchById(customerId), expectedBranch);
}

TEST_F(CustomerOperationsTest, SetCustomerNameById) {
    std::string newName = "Jane Doe";
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_name", customerId, newName, "Customer"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(customerOps->setCustomerNameById(customerId, newName));
    
    // Verify the name was updated in the database
    std::vector<std::string> mockResult = {newName};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_name", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerNameById(customerId), newName);
}

TEST_F(CustomerOperationsTest, SetCustomerPasswordById) {
    std::string newPassword = "newpassword123";
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_password", customerId, newPassword, "Customer"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(customerOps->setCustomerPasswordById(customerId, newPassword));
    
    // Verify the password was updated in the database
    std::vector<std::string> mockResult = {newPassword};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_password", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerPasswordById(customerId), newPassword);
}

TEST_F(CustomerOperationsTest, SetCustomerAccountById) {
    std::string newAccount = "20230914MYS00105";
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_account", customerId, newAccount, "Customer"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(customerOps->setCustomerAccountById(customerId, newAccount));
    
    // Verify the account was updated in the database
    std::vector<std::string> mockResult = {newAccount};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_account", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerAccountById(customerId), newAccount);
}

TEST_F(CustomerOperationsTest, SetCustomerAddressById) {
    std::string newAddress = "456 Elm St";
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_address", customerId, newAddress, "Customer"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(customerOps->setCustomerAddressById(customerId, newAddress));
    
    // Verify the address was updated in the database
    std::vector<std::string> mockResult = {newAddress};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_address", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerAddressById(customerId), newAddress);
}

TEST_F(CustomerOperationsTest, SetCustomerBranchById) {
    std::string newBranch = "MYS002";
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_branch", customerId, newBranch, "Customer"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(customerOps->setCustomerBranchById(customerId, newBranch));
    
    // Verify the branch was updated in the database
    std::vector<std::string> mockResult = {newBranch};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_branch", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    ASSERT_EQ(customerOps->getCustomerBranchById(customerId), newBranch);
}

// Test error handling scenarios
TEST_F(CustomerOperationsTest, GetCustomerNameByIdWithEmptyResult) {
    std::vector<std::string> emptyResult = {};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_name", customerId, "Customer"))
        .WillOnce(testing::Return(emptyResult));
    
    EXPECT_THROW({
        customerOps->getCustomerNameById(customerId);
    }, std::out_of_range);
}

TEST_F(CustomerOperationsTest, DatabaseOperationFailure) {
    // Mock database update failure
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_name", customerId, "New Name", "Customer"))
        .WillOnce(testing::Return(false));
    
    // Should handle database failure gracefully
    EXPECT_NO_THROW({
        customerOps->setCustomerNameById(customerId, "New Name");
    });
}

TEST_F(CustomerOperationsTest, InvalidCustomerId) {
    std::string invalidId = "";
    std::vector<std::string> emptyResult = {};
    
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_name", invalidId, "Customer"))
        .WillOnce(testing::Return(emptyResult));
    
    EXPECT_THROW({
        customerOps->getCustomerNameById(invalidId);
    }, std::out_of_range);
}

TEST_F(CustomerOperationsTest, MultipleCustomersFound) {
    // Test scenario where multiple results are returned (should use first one)
    std::vector<std::string> multipleResults = {"John Doe", "Jane Doe"};
    
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_name", customerId, "Customer"))
        .WillOnce(testing::Return(multipleResults));
        
    std::string result = customerOps->getCustomerNameById(customerId);
    EXPECT_EQ(result, "John Doe"); // Should return first result
}

// ================= processMessage Tests =================

TEST_F(CustomerOperationsTest, ProcessMessage_GetCustomerName) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Customer_name"},
        {"Data", {customerId}}
    };
    
    std::vector<std::string> mockResult = {"John Doe"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_name", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "John Doe");
}

TEST_F(CustomerOperationsTest, ProcessMessage_GetCustomerPassword) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Customer_password"},
        {"Data", {customerId}}
    };
    
    std::vector<std::string> mockResult = {"password123"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_password", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "password123");
}

TEST_F(CustomerOperationsTest, ProcessMessage_GetCustomerAccount) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Customer_account"},
        {"Data", {customerId}}
    };
    
    std::vector<std::string> mockResult = {"20230914MYS00104"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_account", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "20230914MYS00104");
}

TEST_F(CustomerOperationsTest, ProcessMessage_GetCustomerAddress) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Customer_address"},
        {"Data", {customerId}}
    };
    
    std::vector<std::string> mockResult = {"123 Main St"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_address", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "123 Main St");
}

TEST_F(CustomerOperationsTest, ProcessMessage_GetCustomerBranch) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Customer_branch"},
        {"Data", {customerId}}
    };
    
    std::vector<std::string> mockResult = {"MYS001"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Customer_branch", customerId, "Customer"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "MYS001");
}

TEST_F(CustomerOperationsTest, ProcessMessage_SetCustomerName) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Customer_name"},
        {"Data", {customerId, "Jane Doe"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_name", customerId, "Jane Doe", "Customer"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful"); // Default return value
}

TEST_F(CustomerOperationsTest, ProcessMessage_SetCustomerPassword) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Customer_password"},
        {"Data", {customerId, "newpass123"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_password", customerId, "newpass123", "Customer"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful"); // Default return value
}

TEST_F(CustomerOperationsTest, ProcessMessage_SetCustomerAccount) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Customer_account"},
        {"Data", {customerId, "ACC99999"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_account", customerId, "ACC99999", "Customer"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful"); // Default return value
}

TEST_F(CustomerOperationsTest, ProcessMessage_SetCustomerAddress) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Customer_address"},
        {"Data", {customerId, "New Address Street 123"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_address", customerId, "New Address Street 123", "Customer"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful"); // Default return value
}

TEST_F(CustomerOperationsTest, ProcessMessage_SetCustomerBranch) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Customer_branch"},
        {"Data", {customerId, "MYS002"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Customer_branch", customerId, "MYS002", "Customer"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful"); // Default return value
}

TEST_F(CustomerOperationsTest, ProcessMessage_AddCustomer) {
    nlohmann::json message = {
        {"OperationType", "add"},
        {"ColumnName", "Customer"},
        {"Data", {"MYSC00105", "New Customer", "newpass", "New Branch", "New Address", "ACC12345"}}
    };
    
    EXPECT_CALL(*mockDb, buildInsertionQery(testing::_))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful"); // Default return value
}

TEST_F(CustomerOperationsTest, ProcessMessage_DeleteCustomer) {
    nlohmann::json message = {
        {"OperationType", "delete"},
        {"ColumnName", "Customer"},
        {"Data", {customerId}}
    };
    
    EXPECT_CALL(*mockDb, buildDeleteQuery(customerId, "Customer", "Customer_id"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful"); // Default return value
}

TEST_F(CustomerOperationsTest, ProcessMessage_InvalidOperation) {
    nlohmann::json message = {
        {"OperationType", "invalid"},
        {"ColumnName", "Customer_name"},
        {"Data", {customerId}}
    };
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(CustomerOperationsTest, ProcessMessage_InvalidColumnName) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Invalid_column"},
        {"Data", {customerId}}
    };
    
    nlohmann::json result = customerOps->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

} // namespace Banking