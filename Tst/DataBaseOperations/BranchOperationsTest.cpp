/*
 * This content is released under the MIT License as specified in https://raw.githubusercontent.com/gabime/spdlog/master/LICENSE
 */
#include "BranchOperations.hpp"
#include <gtest/gtest.h>

class BranchOperationTestFixture : public ::testing::Test 
{
protected:
    std::shared_ptr<Banking::BranchOperations> BranchOpPtr;
    std::string branchId;

public:
    void SetUp() override;
    void TearDown() override;
};

void BranchOperationTestFixture::SetUp(){
    Banking::Logger::Init();
    // Banking::connection_shptr ptr{std::make_shared<Banking::Connection>()};
    BranchOpPtr = std::make_shared<Banking::BranchOperations>();
    branchId = "MYS002";
    std::string name{"Hebbal Branch"};
    std::string city{"Mysuru"};
    std::string address{"Hebbal"};
    std::string manager{"MYSE00101"};
    BranchOpPtr->addBranch(branchId, name, city, address, manager);
}

void BranchOperationTestFixture::TearDown(){
    BranchOpPtr->deleteBranch(branchId);
}

TEST_F(BranchOperationTestFixture, TestGetBranchNameById) {
    EXPECT_EQ(BranchOpPtr->getBranchNameById(branchId), "Hebbal Branch");
}

TEST_F(BranchOperationTestFixture, TestGetBranchCityById) {
    EXPECT_EQ(BranchOpPtr->getBranchCityById(branchId), "Mysuru");
}

TEST_F(BranchOperationTestFixture, TestGetBranchAddressById) {
    EXPECT_EQ(BranchOpPtr->getBranchAddressById(branchId), "Hebbal");
}

TEST_F(BranchOperationTestFixture, TestGetBranchManagerById) {
    EXPECT_EQ(BranchOpPtr->getBranchManagerById(branchId), "MYSE00101");
}

TEST_F(BranchOperationTestFixture, TestIsActiveBranch) {
    EXPECT_TRUE(BranchOpPtr->isActiveBranch(branchId));
}

TEST_F(BranchOperationTestFixture, TestSetBranchNameById) {
    EXPECT_NO_THROW(BranchOpPtr->setBranchNameById(branchId, "Gokulam Branch"));
}

TEST_F(BranchOperationTestFixture, TestSetBranchCityById) {
    EXPECT_NO_THROW(BranchOpPtr->setBranchCityById(branchId, "Bengaluru"));
}

TEST_F(BranchOperationTestFixture, TestSetBranchAddressById) {
    EXPECT_NO_THROW(BranchOpPtr->setBranchAddressById(branchId, "Gokulam"));
}

TEST_F(BranchOperationTestFixture, TestSetBranchManagerById) {
    EXPECT_NO_THROW(BranchOpPtr->setBranchManagerById(branchId, "MYSE00102"));
}

/* Need to implement the bellow functionality */
// TEST_F(BranchOperationTestFixture, TestSetAsActiveBranch) {
//     EXPECT_NO_THROW(BranchOpPtr->SetAsActiveBranch(branchId));
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}