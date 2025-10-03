/*
 * This content is released under the MIT License as specified in https://raw.githubusercontent.com/gabime/spdlog/master/LICENSE
 */
#include "BranchOperations.hpp"
#include "MockDatabaseOperations.hpp"
#include "Logger.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class BranchOperationTestFixture : public ::testing::Test {
protected:
    std::shared_ptr<testing::StrictMock<Banking::Testing::MockDatabaseOperations>> mockDb;
    std::shared_ptr<Banking::BranchOperations> BranchOpPtr;
    std::string branchId;
    
    void SetUp() override;
    void TearDown() override;
};

void BranchOperationTestFixture::SetUp() {
    Banking::Logger::Init();
    mockDb = std::make_shared<testing::StrictMock<Banking::Testing::MockDatabaseOperations>>();
    BranchOpPtr = std::make_shared<Banking::BranchOperations>(mockDb);
    
    branchId = "MYS002";
    std::string name{"Hebbal Branch"};
    std::string city{"Mysuru"};
    std::string address{"Hebbal"};
    std::string manager{"MYSE00101"};
    
    nlohmann::json branchData;
    branchData.emplace("table", "Branch");
    branchData.emplace("values", nlohmann::json::array());
    auto& branchValues = branchData["values"];
    branchValues.emplace_back(branchId);
    branchValues.emplace_back(name);
    branchValues.emplace_back(city);
    branchValues.emplace_back(address);
    branchValues.emplace_back("ACTIVE");
    branchValues.emplace_back(manager);
    
    // Set up mock expectations for adding branch
    EXPECT_CALL(*mockDb, buildInsertionQery(branchData))
        .WillOnce(testing::Return(true));
    
    BranchOpPtr->addBranch(branchId, name, city, address, manager);
}

void BranchOperationTestFixture::TearDown() {
    // Set up mock expectations for deleting branch
    EXPECT_CALL(*mockDb, buildDeleteQuery(branchId, "Branch", "Branch_id"))
        .WillOnce(testing::Return(true));
    
    BranchOpPtr->deleteBranch(branchId);
}

TEST_F(BranchOperationTestFixture, TestGetBranchNameById) {
    std::vector<std::string> nameResult = {"Hebbal Branch"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_name", branchId, "Branch"))
        .WillOnce(testing::Return(nameResult));
    ASSERT_EQ(BranchOpPtr->getBranchNameById(branchId), "Hebbal Branch");
}

TEST_F(BranchOperationTestFixture, TestGetBranchCityById) {
    std::vector<std::string> cityResult = {"Mysuru"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_city", branchId, "Branch"))
        .WillOnce(testing::Return(cityResult));
    ASSERT_EQ(BranchOpPtr->getBranchCityById(branchId), "Mysuru");
}

TEST_F(BranchOperationTestFixture, TestGetBranchAddressById) {
    std::vector<std::string> addressResult = {"Hebbal"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_address", branchId, "Branch"))
        .WillOnce(testing::Return(addressResult));
    ASSERT_EQ(BranchOpPtr->getBranchAddressById(branchId), "Hebbal");
}

TEST_F(BranchOperationTestFixture, TestGetBranchManagerById) {
    std::vector<std::string> managerResult = {"MYSE00101"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_manager", branchId, "Branch"))
        .WillOnce(testing::Return(managerResult));
    ASSERT_EQ(BranchOpPtr->getBranchManagerById(branchId), "MYSE00101");
}

TEST_F(BranchOperationTestFixture, TestIsActiveBranch) {
    std::vector<std::string> activeResult = {"ACTIVE"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_active", branchId, "Branch"))
        .WillOnce(testing::Return(activeResult));
    ASSERT_TRUE(BranchOpPtr->isActiveBranch(branchId));
}

TEST_F(BranchOperationTestFixture, TestSetBranchNameById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_name", branchId, "Gokulam Branch", "Branch"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(BranchOpPtr->setBranchNameById(branchId, "Gokulam Branch"));
}

TEST_F(BranchOperationTestFixture, TestSetBranchCityById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_city", branchId, "Bengaluru", "Branch"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(BranchOpPtr->setBranchCityById(branchId, "Bengaluru"));
}

TEST_F(BranchOperationTestFixture, TestSetBranchAddressById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_address", branchId, "Gokulam", "Branch"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(BranchOpPtr->setBranchAddressById(branchId, "Gokulam"));
}

TEST_F(BranchOperationTestFixture, TestSetBranchManagerById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_manager", branchId, "MYSE00102", "Branch"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(BranchOpPtr->setBranchManagerById(branchId, "MYSE00102"));
}

/* Need to implement the bellow functionality */
// TEST_F(BranchOperationTestFixture, TestSetAsActiveBranch) {
//     EXPECT_NO_THROW(BranchOpPtr->SetAsActiveBranch(branchId));
// }

// ================= processMessage Tests =================

TEST_F(BranchOperationTestFixture, ProcessMessage_GetBranchName) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Branch_name"},
        {"Data", {branchId}}
    };
    
    std::vector<std::string> mockResult = {"Hebbal Branch"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_name", branchId, "Branch"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Hebbal Branch");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_GetBranchCity) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Branch_city"},
        {"Data", {branchId}}
    };
    
    std::vector<std::string> mockResult = {"Mysuru"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_city", branchId, "Branch"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Mysuru");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_GetBranchAddress) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Branch_address"},
        {"Data", {branchId}}
    };
    
    std::vector<std::string> mockResult = {"Hebbal"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_address", branchId, "Branch"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Hebbal");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_GetBranchManager) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Branch_manager"},
        {"Data", {branchId}}
    };
    
    std::vector<std::string> mockResult = {"MYSE00101"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_manager", branchId, "Branch"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "MYSE00101");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_GetBranchActive) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Branch_active"},
        {"Data", {branchId}}
    };
    
    std::vector<std::string> mockResult = {"ACTIVE"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_active", branchId, "Branch"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "ACTIVE");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_SetBranchName) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Branch_name"},
        {"Data", {branchId, "Gokulam Branch"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_name", branchId, "Gokulam Branch", "Branch"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_SetBranchCity) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Branch_city"},
        {"Data", {branchId, "Bengaluru"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_city", branchId, "Bengaluru", "Branch"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_SetBranchAddress) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Branch_address"},
        {"Data", {branchId, "New Address"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_address", branchId, "New Address", "Branch"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_SetBranchManager) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Branch_manager"},
        {"Data", {branchId, "MYSE00999"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_manager", branchId, "MYSE00999", "Branch"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_AddBranch) {
    nlohmann::json message = {
        {"OperationType", "add"},
        {"ColumnName", "Branch"},
        {"Data", {"MYS999", "New Branch", "New City", "New Address", "MYSE00888"}}
    };
    
    EXPECT_CALL(*mockDb, buildInsertionQery(testing::_))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_DeleteBranch) {
    nlohmann::json message = {
        {"OperationType", "delete"},
        {"ColumnName", "Branch"},
        {"Data", {"MYS888"}}
    };
    
    EXPECT_CALL(*mockDb, buildDeleteQuery("MYS888", "Branch", "Branch_id"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_InvalidOperation) {
    nlohmann::json message = {
        {"OperationType", "invalid"},
        {"ColumnName", "Branch_name"},
        {"Data", {branchId}}
    };
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(BranchOperationTestFixture, ProcessMessage_InvalidColumnName) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Invalid_column"},
        {"Data", {branchId}}
    };
    
    nlohmann::json result = BranchOpPtr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}