// FILE: src/DatabaseOperations/inc/test_CustomerOperations.hpp

#include <gtest/gtest.h>
#include "CustomerOperations.hpp"
#include "Customer.hpp"

namespace Banking {

class CustomerOperationsTest : public ::testing::Test {
protected:
    void SetUp() override {
        Banking::Logger::Init();
        Banking::connection_shptr ptr{std::make_shared<Banking::Connection>()};
        customerOps = std::make_unique<CustomerOperations>(ptr);
        customerId = "MYSC00102";
        Customer newCustomer(customerId, "John Doe", "password123", "MYS001", "123 Main St", "20230914MYS00104");
        customerOps->addCustomer(std::move(newCustomer));
    }

    void TearDown() override {
        customerOps->deleteCustomer(customerId);
    }

    std::unique_ptr<CustomerOperations> customerOps;
    std::string customerId;
};

TEST_F(CustomerOperationsTest, GetCustomerNameById) {
    std::string expectedName = "John Doe";
    // Mock database response or set up the database state
    ASSERT_EQ(customerOps->getCustomerNameById(customerId), expectedName);
}

TEST_F(CustomerOperationsTest, GetCustomerPasswordById) {
    std::string expectedPassword = "password123";
    // Mock database response or set up the database state
    ASSERT_EQ(customerOps->getCustomerPasswordById(customerId), expectedPassword);
}

TEST_F(CustomerOperationsTest, GetCustomerAccountById) {
    std::string expectedAccount = "20230914MYS00104";
    // Mock database response or set up the database state
    ASSERT_EQ(customerOps->getCustomerAccountById(customerId), expectedAccount);
}

TEST_F(CustomerOperationsTest, GetCustomerAddressById) {
    std::string expectedAddress = "123 Main St";
    // Mock database response or set up the database state
    ASSERT_EQ(customerOps->getCustomerAddressById(customerId), expectedAddress);
}

TEST_F(CustomerOperationsTest, GetCustomerBranchById) { 
    std::string expectedBranch = "MYS001";
    // Mock database response or set up the database state
    ASSERT_EQ(customerOps->getCustomerBranchById(customerId), expectedBranch);
}

TEST_F(CustomerOperationsTest, SetCustomerNameById) {
    std::string newName = "Jane Doe";
    ASSERT_NO_THROW(customerOps->setCustomerNameById(customerId, newName));
    // Verify the name was updated in the database
    ASSERT_EQ(customerOps->getCustomerNameById(customerId), newName);
}

TEST_F(CustomerOperationsTest, SetCustomerPasswordById) {
    std::string newPassword = "newpassword123";
    ASSERT_NO_THROW(customerOps->setCustomerPasswordById(customerId, newPassword));
    // Verify the password was updated in the database
    ASSERT_EQ(customerOps->getCustomerPasswordById(customerId), newPassword);
}

TEST_F(CustomerOperationsTest, SetCustomerAccountById) {
    std::string newAccount = "20230914MYS00105";
    ASSERT_NO_THROW(customerOps->setCustomerAccountById(customerId, newAccount));
    // Verify the account was updated in the database
    ASSERT_EQ(customerOps->getCustomerAccountById(customerId), newAccount);
}

TEST_F(CustomerOperationsTest, SetCustomerAddressById) {
    std::string newAddress = "456 Elm St";
    ASSERT_NO_THROW(customerOps->setCustomerAddressById(customerId, newAddress));
    // Verify the address was updated in the database
    ASSERT_EQ(customerOps->getCustomerAddressById(customerId), newAddress);
}

TEST_F(CustomerOperationsTest, SetCustomerBranchById) {
    std::string newBranch = "MYS002";
    ASSERT_NO_THROW(customerOps->setCustomerBranchById(customerId, newBranch));
    // Verify the branch was updated in the database
    ASSERT_EQ(customerOps->getCustomerBranchById(customerId), newBranch);
}

} // namespace Banking