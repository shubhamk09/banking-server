/**
 * @file AccountOperations.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <string>
#include "AccountOperations.hpp"
#include "DatabaseOperations.hpp"

/**
 * @brief Construct a new Banking:: Database Operations:: Account Operations object
 * 
 * @param connPtr 
 */
Banking::AccountOperations::AccountOperations(connection_shptr &connPtr)
{
}

/**
 * @brief 
 * 
 * @param accountId 
 * @return std::string 
 */
std::string Banking::AccountOperations::getAccountBalanceById(const std::string &accountId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Account_balance", accountId, "Account")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param accountId 
 * @return std::string 
 */
nlohmann::json Banking::AccountOperations::getAccountTransactionsById(const std::string &accountId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Account_transactions", accountId, "Account")};
    std::string statement_string_hex {columnVals.at(0)};
    // Convert the hexadecimal string to binary data
    nlohmann::json transactions{createTransactionJson(statement_string_hex, accountId)};
    
    return transactions;
}

/**
 * @brief 
 * 
 * @param accountId 
 * @return std::string 
 */
std::string Banking::AccountOperations::getAccountBranchById(const std::string &accountId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Account_branch", accountId, "Account")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param accountId 
 * @return true 
 * @return false 
 */
bool Banking::AccountOperations::isActiveAccount(const std::string &accountId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Account_active", accountId, "Account")};
    if(columnVals.at(0) == "ACTIVE"){
        return true;
    }
    return false;
}

/**
 * @brief 
 * 
 * @param accNumber 
 * @param newBalance 
 */
void Banking::AccountOperations::setAccountBalanceById(const std::string &accNumber, int newBalance){
    std::string strBalance = std::to_string(newBalance);
    Banking::DatabaseOperations::buildUpdateQuery("Account_balance", accNumber, strBalance, "Account");
}

/**
 * @brief 
 * 
 * @param accNumber 
 * @param newTransaction 
 */
void Banking::AccountOperations::setAccountTransactionById(const std::string &accNumber, nlohmann::json &newTransaction){
    std::string hexJsonData = createHexJson(newTransaction);
    Banking::DatabaseOperations::buildUpdateQuery("Account_transactions", accNumber, hexJsonData, "Account");
}

/**
 * @brief 
 * 
 * @param accNumber 
 * @param newBranch 
 */
void Banking::AccountOperations::setAccountBranchById(const std::string &accNumber, const std::string &newBranch){
    Banking::DatabaseOperations::buildUpdateQuery("Account_branch", accNumber, newBranch, "Account");
}

/**
 * @brief 
 * 
 * @param accNumber 
 */
void Banking::AccountOperations::setAccountStatusById(const std::string &accNumber, bool status){

    std::string accStatus;
    if (status)
    {
        accStatus = "ACTIVE";
    }
    else
    {
        accStatus = "NOTACTIVE";
    }

    Banking::DatabaseOperations::buildUpdateQuery("Account_active", accNumber, accStatus, "Account");
}

/**
 * @brief 
 * 
 * @param accNumber 
 * @param accBalance 
 * @param accTransaction 
 * @param accBranch 
 * @param isActive 
 */
void  Banking::AccountOperations::addAccount(const std::string &accNumber, const std::string &accBalance, nlohmann::json &accTransaction, 
                        const std::string &accBranch, bool &isActive){
    
    std::string accStatus;
    if (isActive)
    {
        accStatus = "ACTIVE";
    }
    else
    {
        accStatus = "NOTACTIVE";
    }

    int balanceInInt{std::stoi(accBalance)};
    
    nlohmann::json AccountData;
    AccountData.emplace("table", "Account");
    AccountData.emplace("values", nlohmann::json::array());
    nlohmann::json& employeeValues = AccountData["values"];
    employeeValues.emplace_back(accNumber);
    employeeValues.emplace_back(balanceInInt);
    employeeValues.emplace_back(createHexJson(accTransaction));
    employeeValues.emplace_back(accBranch);
    employeeValues.emplace_back(accStatus);
    Banking::DatabaseOperations::buildInsertionQery(AccountData);

}

/**
 * @brief 
 * 
 * @param accNumber 
 */
void Banking::AccountOperations::deleteAccount(const std::string &accNumber){
    Banking::DatabaseOperations::buildDeleteQuery(accNumber, "Account", "Account_id");
}

/**
 * @brief 
 * 
 * @param accTransaction 
 * @return std::string 
 */
std::string Banking::AccountOperations::createHexJson(nlohmann::json &accTransaction){
    std::string json_str = accTransaction.dump();
    std::vector<char> json_vector(json_str.begin(), json_str.end());

    // Convert the JSON vector to a hexadecimal string
    std::ostringstream hexData;
    hexData << std::hex << std::uppercase;
    for (char chr : json_vector) {
        hexData << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(chr));
    }
    return hexData.str();
}

/**
 * @brief 
 * 
 * @param hexJson 
 * @return nlohmann::json 
 */
nlohmann::json Banking::AccountOperations::createTransactionJson(std::string &hexJson, const std::string &accNumber){
    std::vector<uint8_t> binaryData;
    nlohmann::json transactions = {};
    if(hexJson!="NULL"){
        for (size_t i = 0; i < hexJson.length(); i += 2) {
        uint8_t byte = std::stoi(hexJson.substr(i, 2), nullptr, 16);
        binaryData.push_back(byte);
        }
        if (!binaryData.empty())
        {
            try {
                std::string jsonData(binaryData.begin(), binaryData.end());
                transactions = nlohmann::json::parse(jsonData);
            } catch (const std::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }
        else
        {
            BANKING_LOGGER_ERROR("Error transaction not available for {}", accNumber);
        }
    }
    else{
        BANKING_LOGGER_INFO("Transaction not available for {}", accNumber);
    }
    return transactions;
}

nlohmann::json Banking::AccountOperations::processMessage(const nlohmann::json& message)
{
    std::string operationType = message.at("OperationType");
    std::string columnName = message.at("ColumnName");
    nlohmann::json data = message.at("Data");

    if (operationType == "get") {
        if (columnName == "Account_balance") {
            return getAccountBalanceById(data.at(0));
        } else if (columnName == "Account_transactions") {
            return getAccountTransactionsById(data.at(0)).dump();
        } else if (columnName == "Account_branch") {
            return getAccountBranchById(data.at(0));
        } else if (columnName == "Account_active") {
            return isActiveAccount(data.at(0)) ? "ACTIVE" : "NOTACTIVE";
        }
    } else if (operationType == "set") {
        if (columnName == "Account_balance") {
            setAccountBalanceById(data.at(0), std::stoi(static_cast<std::string>(data.at(1))));
        } else if (columnName == "Account_transactions") {
            nlohmann::json transaction = data.at(1);
            setAccountTransactionById(data.at(0), transaction);
        } else if (columnName == "Account_branch") {
            setAccountBranchById(data.at(0), data.at(1));
        } else if (columnName == "Account_active") {
            setAccountStatusById(data.at(0), data.at(1) == "ACTIVE");
        }
    } else if (operationType == "add") {
        nlohmann::json transaction = data.at(2);
        bool isActive = data.at(4) == "ACTIVE";
        addAccount(data.at(0), data.at(1), transaction, data.at(3), isActive);
    } else if (operationType == "delete") {
        deleteAccount(data.at(0));
    }

    return "Operation was not successful";
    // Handle other operations or return an error message
    // TO-DO: return nlohmann::json::object({{"error", "Invalid operation type"}});
}
