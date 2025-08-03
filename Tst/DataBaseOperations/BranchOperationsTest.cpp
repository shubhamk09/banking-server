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