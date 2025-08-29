#include "Customer.hpp"
#include "Employee.hpp"
#include <gtest/gtest.h>

class CustomerTestFixture: public testing::Test
{
protected:
    std::shared_ptr<Banking::Customer> newCustomer;
public:
    void SetUp() override;
};

void CustomerTestFixture::SetUp(){
    std::shared_ptr<Banking::User> newUser {Banking::User::createUser("MYSC00123", "name", "password", "address", "branch", "123456789")};
    newCustomer = std::dynamic_pointer_cast<Banking::Customer>(newUser);
}

TEST_F(CustomerTestFixture, TestGetId) {
    ASSERT_EQ(newCustomer->getId(), "MYSC00123");
}

TEST_F(CustomerTestFixture, TestGetName) {
    ASSERT_EQ(newCustomer->getName(), "name");
}

TEST_F(CustomerTestFixture, TestGetPassword) {
   ASSERT_EQ(newCustomer->getPassword(), "password");
}

TEST_F(CustomerTestFixture, TestGetBranch) {
    ASSERT_EQ(newCustomer->getBranch(), "branch");
}

TEST_F(CustomerTestFixture, TestGetAddress) {
    ASSERT_EQ(newCustomer->getAddress(), "address");
}

TEST_F(CustomerTestFixture, TestGetAccNumber) {
    ASSERT_EQ(newCustomer->getAccountNumber(), "123456789");
}

TEST_F(CustomerTestFixture, TestSetId){
    newCustomer->setId("121");
    ASSERT_EQ(newCustomer->getId(), "121");
}

TEST_F(CustomerTestFixture, TestSetName){
    newCustomer->setName("shubham");
    ASSERT_EQ(newCustomer->getName(), "shubham");
}

TEST_F(CustomerTestFixture, TestSetPassword){
    newCustomer->setPassword("shannu");
    ASSERT_EQ(newCustomer->getPassword(), "shannu");
}

TEST_F(CustomerTestFixture, TestSetBranch){
    newCustomer->setBranch("Mowa");
    ASSERT_EQ(newCustomer->getBranch(), "Mowa");
}

TEST_F(CustomerTestFixture, TestSetAddress){
    newCustomer->setAddress("Mowa, daldal seoni");
    ASSERT_EQ(newCustomer->getAddress(), "Mowa, daldal seoni");
}

TEST_F(CustomerTestFixture, TestSetAccNumber){
    newCustomer->setAccountNumber("123456789");
    ASSERT_EQ(newCustomer->getAccountNumber(), "123456789");
}

// The invalid id has been passed here
TEST(UserTest, InvalidUserTest){
    std::shared_ptr<Banking::User> newUser = {Banking::User::createUser("MYSD00123", "name", "password", "address", "branch", "123456789")};
    ASSERT_TRUE(newUser == nullptr);
}

// Test User factory method with valid Customer ID
TEST(UserTest, ValidCustomerCreationTest) {
    std::shared_ptr<Banking::User> newUser = Banking::User::createUser("MYSC00123", "John", "pass123", "123 Main St", "NYC Branch", "ACC123456");
    ASSERT_NE(newUser, nullptr);
    
    // Test polymorphic behavior
    std::shared_ptr<Banking::Customer> customer = std::dynamic_pointer_cast<Banking::Customer>(newUser);
    ASSERT_NE(customer, nullptr);
    ASSERT_EQ(customer->getAccountNumber(), "ACC123456");
}

// Test User factory method with valid Employee ID  
TEST(UserTest, ValidEmployeeCreationTest) {
    std::shared_ptr<Banking::User> newUser = Banking::User::createUser("MYSE00123", "Jane", "pass456", "456 Oak St", "LA Branch", "Manager");
    ASSERT_NE(newUser, nullptr);
    
    // Test polymorphic behavior
    std::shared_ptr<Banking::Employee> employee = std::dynamic_pointer_cast<Banking::Employee>(newUser);
    ASSERT_NE(employee, nullptr);
    ASSERT_EQ(employee->getDesignation(), "Manager");
}

// Test edge cases for User creation
TEST(UserTest, EdgeCaseTests) {
    // Test with empty strings
    std::shared_ptr<Banking::User> emptyUser = Banking::User::createUser("MYSC00123", "", "", "", "", "");
    ASSERT_NE(emptyUser, nullptr); // Should still create user even with empty fields
    
    // Test with very long strings
    std::string longString(1000, 'A');
    std::shared_ptr<Banking::User> longStringUser = Banking::User::createUser("MYSC00123", longString, longString, longString, longString, longString);
    ASSERT_NE(longStringUser, nullptr);
    
    // Test with special characters
    std::shared_ptr<Banking::User> specialCharUser = Banking::User::createUser("MYSC00123", "John@#$%", "pass!@#", "123 Main St.", "NYC-Branch", "ACC-123456");
    ASSERT_NE(specialCharUser, nullptr);
}
