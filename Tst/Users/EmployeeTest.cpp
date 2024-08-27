#include "Employee.hpp"
#include <gtest/gtest.h>

class EmployeeTestFixture: public testing::Test
{
protected:
    std::shared_ptr<Banking::Employee> newEmployee;
public:
    void SetUp() override;
};

void EmployeeTestFixture::SetUp(){
    std::shared_ptr<Banking::User> newUser {Banking::User::createUser("MYSE00122", "name", "password", "address", "branch", "manager")};
    newEmployee = std::dynamic_pointer_cast<Banking::Employee>(newUser);
}

TEST_F(EmployeeTestFixture, TestGetId) {
    ASSERT_EQ(newEmployee->getId(), "MYSE00122");
}

TEST_F(EmployeeTestFixture, TestGetName) {
    ASSERT_EQ(newEmployee->getName(), "name");
}

TEST_F(EmployeeTestFixture, TestGetPassword) {
   ASSERT_EQ(newEmployee->getPassword(), "password");
}

TEST_F(EmployeeTestFixture, TestGetBranch) {
    ASSERT_EQ(newEmployee->getBranch(), "branch");
}

TEST_F(EmployeeTestFixture, TestGetAddress) {
    ASSERT_EQ(newEmployee->getAddress(), "address");
}

TEST_F(EmployeeTestFixture, TestGetDesignamtion) {
    ASSERT_EQ(newEmployee->getDesignation(), "manager");
}

TEST_F(EmployeeTestFixture, TestSetId){
    newEmployee->setId("121");
    ASSERT_EQ(newEmployee->getId(), "121");
}

TEST_F(EmployeeTestFixture, TestSetName){
    newEmployee->setName("shubham");
    ASSERT_EQ(newEmployee->getName(), "shubham");
}

TEST_F(EmployeeTestFixture, TestSetPassword){
    newEmployee->setPassword("shannu");
    ASSERT_EQ(newEmployee->getPassword(), "shannu");
}

TEST_F(EmployeeTestFixture, TestSetBranch){
    newEmployee->setBranch("Mowa");
    ASSERT_EQ(newEmployee->getBranch(), "Mowa");
}

TEST_F(EmployeeTestFixture, TestSetAddress){
    newEmployee->setAddress("Mowa, daldal seoni");
    ASSERT_EQ(newEmployee->getAddress(), "Mowa, daldal seoni");
}

TEST_F(EmployeeTestFixture, TestSetDesignation){
    newEmployee->setDesignation("Manager");
    ASSERT_EQ(newEmployee->getDesignation(), "Manager");
}
