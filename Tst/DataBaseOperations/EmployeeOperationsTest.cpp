#include "EmployeeOperations.hpp"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class EmployeeOperationTestFixture: public testing::Test
{
protected:
    std::shared_ptr<Banking::EmployeeOperations> EmployeeOpPtr;
    std::string empid;
public:
    void SetUp() override;
    void TearDown() override;
};

void EmployeeOperationTestFixture::SetUp(){
    Banking::connection_shptr ptr{std::make_shared<Banking::Connection>()};
    EmployeeOpPtr = std::make_shared<Banking::EmployeeOperations>(ptr);
    empid = "MYSE00102";
    std::string name{"Shubham Kalihari"};
    std::string password{"Shannu"};
    std::string designation{"Cashier"};
    std::string address{"Shivmoga"};
    std::string branch{"MYS001"};
    Banking::Employee newEmployee {empid, name, password, branch, address, designation};
    EmployeeOpPtr->addEmployee(std::move(newEmployee));
}

void EmployeeOperationTestFixture::TearDown(){
    EmployeeOpPtr->deleteEmployee(empid);
}

TEST_F(EmployeeOperationTestFixture, GetterTest) {
    ASSERT_EQ(EmployeeOpPtr->getEmployeeNameById(empid), "Shubham Kalihari");
    ASSERT_EQ(EmployeeOpPtr->getEmployeePasswordById(empid), "Shannu");
    ASSERT_EQ(EmployeeOpPtr->getEmployeeDesignationById(empid), "Cashier");
    ASSERT_EQ(EmployeeOpPtr->getEmployeeAddressById(empid), "Shivmoga");
    ASSERT_EQ(EmployeeOpPtr->getEmployeeBranchById(empid), "MYS001");
}