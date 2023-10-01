#include "Employee.hpp"
#include <gtest/gtest.h>

class EmployeeTestFixture: public testing::Test
{
protected:
    std::shared_ptr<Banking::Employee> newUser;
public:
    void SetUp() override;
};

void EmployeeTestFixture::SetUp(){
    newUser = std::make_shared<Banking::Employee>("111", "name", "password", "branch", "address", "manager");
}


TEST_F(EmployeeTestFixture, TestGetId) {
    ASSERT_EQ(newUser->getId(), "111");
}

TEST_F(EmployeeTestFixture, TestGetName) {
    ASSERT_EQ(newUser->getName(), "name");
}

TEST_F(EmployeeTestFixture, TestGetPassword) {
   ASSERT_EQ(newUser->getPassword(), "password");
}

TEST_F(EmployeeTestFixture, TestGetBranch) {
    ASSERT_EQ(newUser->getBranch(), "branch");
}

TEST_F(EmployeeTestFixture, TestGetAddress) {
    ASSERT_EQ(newUser->getAddress(), "address");
}

TEST_F(EmployeeTestFixture, TestGetDesignamtion) {
    ASSERT_EQ(newUser->getDesignation(), "manager");
}