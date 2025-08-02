#include "EmployeeOperations.hpp"
#include "MockDatabaseOperations.hpp"
#include "Logger.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class EmployeeOperationTestFixture: public testing::Test
{
protected:
    std::shared_ptr<Banking::Testing::MockDatabaseOperations> mockDb;
    std::shared_ptr<Banking::EmployeeOperations> EmployeeOpPtr;
    std::string empid;
public:
    void SetUp() override;
    void TearDown() override;
};

void EmployeeOperationTestFixture::SetUp(){
    Banking::Logger::Init();
    mockDb = std::make_shared<testing::StrictMock<Banking::Testing::MockDatabaseOperations>>();
    EmployeeOpPtr = std::make_shared<Banking::EmployeeOperations>(mockDb);
    
    empid = "MYSE00102";
    std::string name{"Shubham Kalihari"};
    std::string password{"Shannu"};
    std::string designation{"Cashier"};
    std::string address{"Shivmoga"};
    std::string branch{"MYS001"};
    
    // Set up mock expectations for adding employee
    EXPECT_CALL(*mockDb, buildInsertionQery(testing::_))
        .Times(2)  // Once for Employee table, once for EmployeeToBranch table
        .WillRepeatedly(testing::Return(true));
        
    Banking::Employee newEmployee {empid, name, password, branch, address, designation};
    EmployeeOpPtr->addEmployee(std::move(newEmployee));
}

void EmployeeOperationTestFixture::TearDown(){
    // Set up mock expectations for deleting employee
    EXPECT_CALL(*mockDb, buildDeleteQuery(empid, "Employee", "Employee_id"))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*mockDb, buildDeleteQuery(empid, "EmployeeToBranch", "Employee_id"))
        .WillOnce(testing::Return(true));
        
    EmployeeOpPtr->deleteEmployee(empid);
}

TEST_F(EmployeeOperationTestFixture, GetterTest) {
    // Set up mock expectations for getters
    std::vector<std::string> nameResult = {"Shubham Kalihari"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_name", empid, "Employee"))
        .WillOnce(testing::Return(nameResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeeNameById(empid), "Shubham Kalihari");

    std::vector<std::string> passwordResult = {"Shannu"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_password", empid, "Employee"))
        .WillOnce(testing::Return(passwordResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeePasswordById(empid), "Shannu");

    std::vector<std::string> designationResult = {"Cashier"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_designation", empid, "Employee"))
        .WillOnce(testing::Return(designationResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeeDesignationById(empid), "Cashier");

    std::vector<std::string> addressResult = {"Shivmoga"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_address", empid, "Employee"))
        .WillOnce(testing::Return(addressResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeeAddressById(empid), "Shivmoga");

    std::vector<std::string> branchResult = {"MYS001"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_id", empid, "EmployeeToBranch", "Employee_id"))
        .WillOnce(testing::Return(branchResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeeBranchById(empid), "MYS001");
}

TEST_F(EmployeeOperationTestFixture, SetNameTest) {
    // Test setEmployeeNameById
    EXPECT_CALL(*mockDb, buildUpdateQuery("Employee_name", empid, "Yukku", "Employee"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(EmployeeOpPtr->setEmployeeNameById(empid, "Yukku"));

    std::vector<std::string> nameResult = {"Yukku"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_name", empid, "Employee"))
        .WillOnce(testing::Return(nameResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeeNameById(empid), "Yukku");
}

TEST_F(EmployeeOperationTestFixture, SetPasswordTest) {
    // Test setEmployeePasswordById
    EXPECT_CALL(*mockDb, buildUpdateQuery("Employee_password", empid, "password_is_something", "Employee"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(EmployeeOpPtr->setEmployeePasswordById(empid, "password_is_something"));

    std::vector<std::string> passwordResult = {"password_is_something"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_password", empid, "Employee"))
        .WillOnce(testing::Return(passwordResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeePasswordById(empid), "password_is_something");
}

TEST_F(EmployeeOperationTestFixture, SetAddressTest) {
    // Test setEmployeeAddressById
    EXPECT_CALL(*mockDb, buildUpdateQuery("Employee_address", empid, "Address is something", "Employee"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(EmployeeOpPtr->setEmployeeAddressById(empid, "Address is something"));

    std::vector<std::string> addressResult = {"Address is something"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_address", empid, "Employee"))
        .WillOnce(testing::Return(addressResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeeAddressById(empid), "Address is something");
}

TEST_F(EmployeeOperationTestFixture, SetBranchTest) {
    // Test setEmployeeBranchById
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_id", empid, "MYS002", "EmployeeToBranch", "Employee_id"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(EmployeeOpPtr->setEmployeeBranchById(empid, "MYS002"));

    std::vector<std::string> branchResult = {"MYS002"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_id", empid, "EmployeeToBranch", "Employee_id"))
        .WillOnce(testing::Return(branchResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeeBranchById(empid), "MYS002");

    // Set back to original value
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_id", empid, "MYS001", "EmployeeToBranch", "Employee_id"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(EmployeeOpPtr->setEmployeeBranchById(empid, "MYS001"));
}

TEST_F(EmployeeOperationTestFixture, SetDesignationTest) {
    // Mock the getEmployeeBranchById call that happens inside setEmployeeDesignationById
    std::vector<std::string> branchResult = {"MYS001"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_id", empid, "EmployeeToBranch", "Employee_id"))
        .WillOnce(testing::Return(branchResult));
    
    // Mock the check for existing managers in the branch (empty result means no manager)
    std::vector<std::string> employeesInBranch = {};  // Empty result to avoid manager conflict
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_id", "MYS001", "EmployeeToBranch", "Branch_id"))
        .WillOnce(testing::Return(employeesInBranch));
    
    // Test setEmployeeDesignationById
    EXPECT_CALL(*mockDb, buildUpdateQuery("Employee_designation", empid, "Manager", "Employee"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(EmployeeOpPtr->setEmployeeDesignationById(empid, "Manager"));

    std::vector<std::string> designationResult = {"Manager"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Employee_designation", empid, "Employee"))
        .WillOnce(testing::Return(designationResult));
    ASSERT_EQ(EmployeeOpPtr->getEmployeeDesignationById(empid), "Manager");

    // Set back to original value
    EXPECT_CALL(*mockDb, buildUpdateQuery("Employee_designation", empid, "Cashier", "Employee"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(EmployeeOpPtr->setEmployeeDesignationById(empid, "Cashier"));
}