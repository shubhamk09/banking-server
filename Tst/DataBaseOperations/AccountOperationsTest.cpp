#include "AccountOperations.hpp"
#include "MockDatabaseOperations.hpp"
#include "Logger.hpp"
#include <nlohmann/json.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iomanip>

class AccountOperationsTestFixture: public testing::Test
{
protected:
    std::shared_ptr<testing::StrictMock<Banking::Testing::MockDatabaseOperations>> mockDb;
    std::shared_ptr<Banking::AccountOperations> accOpt_ptr;
    std::string newAccNum;
    nlohmann::json jsonString1;
    
    // Helper function to create hex encoded JSON like AccountOperations does
    std::string createHexJson(const nlohmann::json& json) {
        std::string json_str = json.dump();
        std::vector<char> json_vector(json_str.begin(), json_str.end());
        
        std::ostringstream hexData;
        hexData << std::hex << std::uppercase;
        for (char chr : json_vector) {
            hexData << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(chr));
        }
        return hexData.str();
    }
    
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
    accountData["values"].push_back(std::stoi(newBal));  // Balance as integer
    accountData["values"].push_back(createHexJson(jsonString1));  // JSON as hex
    accountData["values"].push_back(newBranch);
    accountData["values"].push_back(activeornot ? "ACTIVE" : "NOTACTIVE");

    EXPECT_CALL(*mockDb, buildInsertionQery(accountData))
        .WillOnce(testing::Return(true));
    
    accOpt_ptr->addAccount(newAccNum, newBal, jsonString1, newBranch, activeornot);
}

void AccountOperationsTestFixture::TearDown() {
    EXPECT_CALL(*mockDb, buildDeleteQuery(newAccNum, "Account", "Account_id"))
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
    std::string hexTransactionString = createHexJson(jsonString1);
    std::vector<std::string> transResult = {hexTransactionString};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_transactions", newAccNum, "Account"))
        .WillOnce(testing::Return(transResult));
    auto transactions = accOpt_ptr->getAccountTransactionsById(newAccNum);
    ASSERT_FALSE(transactions.empty());
}

TEST_F(AccountOperationsTestFixture, TestGetAccountBranchById) {
    std::vector<std::string> branchResult = {"MYS001"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_branch", newAccNum, "Account"))
        .WillOnce(testing::Return(branchResult));
    ASSERT_EQ(accOpt_ptr->getAccountBranchById(newAccNum), "MYS001");
}

TEST_F(AccountOperationsTestFixture, TestIsActiveAccount) {
    std::vector<std::string> statusResult = {"ACTIVE"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_active", newAccNum, "Account"))
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

    std::string hexTransactionString = createHexJson(transactionString);
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_transactions", newAccNum, hexTransactionString, "Account"))
        .WillOnce(testing::Return(true));
    // Need to make a copy since method expects non-const reference
    nlohmann::json transactionCopy = transactionString;
    ASSERT_NO_THROW(accOpt_ptr->setAccountTransactionById(newAccNum, transactionCopy));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountBranchById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_branch", newAccNum, "MYS001", "Account"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(accOpt_ptr->setAccountBranchById(newAccNum, "MYS001"));
}

TEST_F(AccountOperationsTestFixture, TestSetAccountStatusById) {
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_active", newAccNum, "NOTACTIVE", "Account"))
        .WillOnce(testing::Return(true));
    ASSERT_NO_THROW(accOpt_ptr->setAccountStatusById(newAccNum, false));
}

// ================= processMessage Tests =================

TEST_F(AccountOperationsTestFixture, ProcessMessage_GetAccountBalance) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Account_balance"},
        {"Data", {newAccNum}}
    };
    
    std::vector<std::string> mockResult = {"5000"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_balance", newAccNum, "Account"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "5000");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_GetAccountTransactions) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Account_transactions"},
        {"Data", {newAccNum}}
    };
    
    std::string hexTransaction = createHexJson(jsonString1);
    std::vector<std::string> mockResult = {hexTransaction};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_transactions", newAccNum, "Account"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    // Result should be the JSON dump of the transaction
    EXPECT_TRUE(result.is_string());
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_GetAccountBranch) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Account_branch"},
        {"Data", {newAccNum}}
    };
    
    std::vector<std::string> mockResult = {"MYS001"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_branch", newAccNum, "Account"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "MYS001");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_GetAccountActive) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Account_active"},
        {"Data", {newAccNum}}
    };
    
    std::vector<std::string> mockResult = {"ACTIVE"};
    EXPECT_CALL(*mockDb, buildSelectionQuery("Account_active", newAccNum, "Account"))
        .WillOnce(testing::Return(mockResult));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "ACTIVE");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_SetAccountBalance) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Account_balance"},
        {"Data", {newAccNum, "7500"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_balance", newAccNum, "7500", "Account"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_SetAccountTransactions) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Account_transactions"},
        {"Data", {newAccNum, jsonString1}}
    };
    
    std::string hexTransaction = createHexJson(jsonString1);
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_transactions", newAccNum, hexTransaction, "Account"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_SetAccountBranch) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Account_branch"},
        {"Data", {newAccNum, "MYS002"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_branch", newAccNum, "MYS002", "Account"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_SetAccountActive) {
    nlohmann::json message = {
        {"OperationType", "set"},
        {"ColumnName", "Account_active"},
        {"Data", {newAccNum, "ACTIVE"}}
    };
    
    EXPECT_CALL(*mockDb, buildUpdateQuery("Account_active", newAccNum, "ACTIVE", "Account"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_AddAccount) {
    nlohmann::json message = {
        {"OperationType", "add"},
        {"ColumnName", "Account"},
        {"Data", {"ACC123456", "5000", jsonString1, "MYS001", "ACTIVE"}}
    };
    
    std::string hexTransaction = createHexJson(jsonString1);
    EXPECT_CALL(*mockDb, buildInsertionQery(testing::_))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_DeleteAccount) {
    nlohmann::json message = {
        {"OperationType", "delete"},
        {"ColumnName", "Account"},
        {"Data", {"ACC999999"}}
    };
    
    EXPECT_CALL(*mockDb, buildDeleteQuery("ACC999999", "Account", "Account_id"))
        .WillOnce(testing::Return(true));
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_InvalidOperation) {
    nlohmann::json message = {
        {"OperationType", "invalid"},
        {"ColumnName", "Account_balance"},
        {"Data", {newAccNum}}
    };
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}

TEST_F(AccountOperationsTestFixture, ProcessMessage_InvalidColumnName) {
    nlohmann::json message = {
        {"OperationType", "get"},
        {"ColumnName", "Invalid_column"},
        {"Data", {newAccNum}}
    };
    
    nlohmann::json result = accOpt_ptr->processMessage(message);
    EXPECT_EQ(result, "Operation was not successful");
}