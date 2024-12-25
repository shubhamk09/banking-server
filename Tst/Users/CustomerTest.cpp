#include "Customer.hpp"
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
