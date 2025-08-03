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

} // namespace Banking