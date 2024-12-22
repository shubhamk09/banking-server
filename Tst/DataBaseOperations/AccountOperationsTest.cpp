#include "AccountOperations.hpp"
#include <nlohmann/json.hpp>
#include <gtest/gtest.h>

class AccountOperationsTestFixture: public testing::Test
{
protected:
    std::shared_ptr<Banking::AccountOperations> accOpt_ptr;
    std::string newAccNum;
public:
    void SetUp() override;
    void TearDown() override;
};

void AccountOperationsTestFixture::SetUp(){
    Banking::connection_shptr conn_ptr{std::make_shared<Banking::Connection>()};
    accOpt_ptr = std::make_shared<Banking::AccountOperations>(conn_ptr);
    nlohmann::json jsonString1 = R"({
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
    newAccNum = {"20230914MYS00103"};
    std::string newBal{"2000"};
    bool activeornot{true};
    std::string newBranch{"MYS001"};
    accOpt_ptr->addAccount(newAccNum, newBal, jsonString1, newBranch, activeornot);
}

void AccountOperationsTestFixture::TearDown(){
    accOpt_ptr->deleteAccount(newAccNum);;
}

TEST_F(AccountOperationsTestFixture, TestGetBalanceById) {
    ASSERT_EQ(accOpt_ptr->getAccountBalanceById(newAccNum), "2000");
}

TEST_F(AccountOperationsTestFixture, TestGetAccountTransactionsById) {
    auto transactions = accOpt_ptr->getAccountTransactionsById(newAccNum);
    ASSERT_FALSE(transactions.empty());
}

TEST_F(AccountOperationsTestFixture, TestGetAccountBranchById) {
   ASSERT_EQ(accOpt_ptr->getAccountBranchById(newAccNum), "MYS001");
}

TEST_F(AccountOperationsTestFixture, TestIsActiveAccount) {
   ASSERT_TRUE(accOpt_ptr->isActiveAccount(newAccNum));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountBalanceById) {
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
    ASSERT_NO_THROW(accOpt_ptr->setAccountTransactionById(newAccNum, transactionString));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountBranchById) {
   ASSERT_NO_THROW(accOpt_ptr->setAccountBranchById(newAccNum, "MYS001"));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountStatusById) {
   ASSERT_NO_THROW(accOpt_ptr->setAccountStatusById(newAccNum, false));
}