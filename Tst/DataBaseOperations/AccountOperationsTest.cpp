#include "AccountOperations.hpp"
#include "MockDatabaseOperations.hpp"
#include "Logger.hpp"
#include <nlohmann/json.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class AccountOperationsTestFixture: public testing::Test
{
protected:
    std::shared_ptr<testing::StrictMock<Banking::Testing::MockDatabaseOperations>> mockDb;
    std::shared_ptr<Banking::AccountOperations> accOpt_ptr;
    std::string newAccNum;
    nlohmann::json jsonString1;
public:
    void SetUp() override;
    void TearDown() override;
};

void AccountOperationsTestFixture::SetUp() {
    Banking::Logger::Init();
    mockDb = std::make_shared<testing::StrictMock<Banking::Testing::MockDatabaseOperations>>();
    accOpt_ptr = std::make_shared<Banking::AccountOperations>(mockDb);
    
    jsonString1 = R"({
            "pi": 3.141,
            "happy": true,
            "name": "Niels",
            "nothing": null,
            "answer": {
                "everything": 42
            },
            "list": [1, 0, 2],
            "object": {
                "currency": "USD",
                "value": 42.99
            }
        })"_json;
    
    newAccNum = "20230914MYS00103";
    std::string newBal = "2000";
    bool activeornot = true;
    std::string newBranch = "MYS001";

    // Set up mock for account creation
    nlohmann::json accountData;
    accountData["table"] = "Account";
    accountData["values"] = nlohmann::json::array();
    accountData["values"].push_back(newAccNum);
    accountData["values"].push_back(newBal);
    accountData["values"].push_back(jsonString1.dump());
    accountData["values"].push_back(newBranch);
    accountData["values"].push_back(activeornot ? "ACTIVE" : "INACTIVE");

    EXPECT_CALL(*mockDb, buildInsertionQery(accountData))
        .WillOnce(testing::Return(true));
    
    accOpt_ptr->addAccount(newAccNum, newBal, jsonString1, newBranch, activeornot);
}

void AccountOperationsTestFixture::TearDown() {
    EXPECT_CALL(*mockDb, buildDeleteQuery(newAccNum, "Account", "Account_number"))
        .WillOnce(testing::Return(true));
    
    accOpt_ptr->deleteAccount(newAccNum);
}

TEST_F(AccountOperationsTestFixture, TestGetBalanceById) {
    std::vector<std::string> balanceResult = {"2000"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_balance", newAccNum, "Account"))
        .WillOnce(testing::Return(balanceResult));
    ASSERT_EQ(accOpt_ptr->getAccountBalanceById(newAccNum), "2000");
}

TEST_F(AccountOperationsTestFixture, TestGetAccountTransactionsById) {
    std::vector<std::string> transResult = {jsonString1.dump()};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_transactions", newAccNum, "Account"))
        .WillOnce(testing::Return(transResult));
    auto transactions = accOpt_ptr->getAccountTransactionsById(newAccNum);
    ASSERT_FALSE(transactions.empty());
}

TEST_F(AccountOperationsTestFixture, TestGetAccountBranchById) {
    std::vector<std::string> branchResult = {"MYS001"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Branch_id", newAccNum, "Account"))
        .WillOnce(testing::Return(branchResult));
    ASSERT_EQ(accOpt_ptr->getAccountBranchById(newAccNum), "MYS001");
}

TEST_F(AccountOperationsTestFixture, TestIsActiveAccount) {
    std::vector<std::string> statusResult = {"ACTIVE"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_status", newAccNum, "Account"))
        .WillOnce(testing::Return(statusResult));
    ASSERT_TRUE(accOpt_ptr->isActiveAccount(newAccNum));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountBalanceById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_balance", newAccNum, "3000", "Account"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(accOpt_ptr->setAccountBalanceById(newAccNum, 3000));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountTransactionById) {
    nlohmann::json transactionString = R"({
            "pi": 3.141,
            "happy": true,
            "name": "Niels",
            "nothing": null,
            "answer": {
                "everything": 42
            },
            "list": [1, 0, 2],
            "object": {
                "currency": "USD",
                "value": 42.99
            }
        })"_json;

    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_transactions", newAccNum, transactionString.dump(), "Account"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(accOpt_ptr->setAccountTransactionById(newAccNum, transactionString));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountBranchById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Branch_id", newAccNum, "MYS001", "Account"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(accOpt_ptr->setAccountBranchById(newAccNum, "MYS001"));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountStatusById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_status", newAccNum, "INACTIVE", "Account"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(accOpt_ptr->setAccountStatusById(newAccNum, false));
}