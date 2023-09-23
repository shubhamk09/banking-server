/**
 * @file AccountOperations.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "AccountOperations.hpp"

/**
 * @brief Construct a new Banking:: Database Operations:: Account Operations object
 * 
 * @param connPtr 
 */
Banking::AccountOperations::AccountOperations(connection_shptr &connPtr): Banking::DatabaseOperations{connPtr}
{
}

/**
 * @brief 
 * 
 * @param accountId 
 * @return std::string 
 */
std::string Banking::AccountOperations::getAccountBalanceById(std::string &accountId){
    std::string colName = "Account_balance";
    std::string tableName = "Account";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, accountId, tableName)};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param accountId 
 * @return std::string 
 */
nlohmann::json Banking::AccountOperations::getAccountTransactionsById(std::string &accountId){
    std::string colName = "Account_transactions";
    std::string tableName = "Account";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, accountId, tableName)};
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
std::string Banking::AccountOperations::getAccountBranchById(std::string &accountId){
    std::string colName = "Account_branch";
    std::string tableName = "Account";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, accountId, tableName)};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param accountId 
 * @return true 
 * @return false 
 */
bool Banking::AccountOperations::isActiveAccount(std::string &accountId){
    std::string colName = "Account_active";
    std::string tableName = "Account";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, accountId, tableName)};
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
void Banking::AccountOperations::setAccountBalanceById(std::string &accNumber, int newBalance){
    std::string colName = "Account_balance";
    std::string tableName = "Account";
    std::string strBalance = std::to_string(newBalance);
    Banking::DatabaseOperations::buildUpdateQuery(colName, accNumber, strBalance, tableName);
}

/**
 * @brief 
 * 
 * @param accNumber 
 * @param newTransaction 
 */
void Banking::AccountOperations::setAccountTransactionById(std::string &accNumber, nlohmann::json &newTransaction){
    std::string colName = "Account_transactions";
    std::string tableName = "Account";
    std::string hexJsonData = createHexJson(newTransaction);
    Banking::DatabaseOperations::buildUpdateQuery(colName, accNumber, hexJsonData, tableName);
}

/**
 * @brief 
 * 
 * @param accNumber 
 * @param newBranch 
 */
void Banking::AccountOperations::setAccountBranchById(std::string &accNumber, std::string &newBranch){
    std::string colName = "Account_branch";
    std::string tableName = "Account"; 
    Banking::DatabaseOperations::buildUpdateQuery(colName, accNumber, newBranch, tableName);
}

/**
 * @brief 
 * 
 * @param accNumber 
 */
void Banking::AccountOperations::setAccountStatusById(std::string &accNumber, bool status){
    std::string colName = "Account_active";
    std::string tableName = "Account";
    std::string accStatus;
    if (status)
    {
        accStatus = "ACTIVE";
    }
    else
    {
        accStatus = "NOTACTIVE";
    }

    Banking::DatabaseOperations::buildUpdateQuery(colName, accNumber, accStatus, tableName);
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
void  Banking::AccountOperations::addAccount(std::string &accNumber, std::string &accBalance, nlohmann::json &accTransaction, 
                        std::string &accBranch, bool &isActive){
    
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
void Banking::AccountOperations::deleteAccount(std::string &accNumber){
    std::string tableName = "Account";
    std::string searchOn = "Account_id";
    Banking::DatabaseOperations::buildDeleteQuery(accNumber, tableName, searchOn);
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
nlohmann::json Banking::AccountOperations::createTransactionJson(std::string &hexJson, std::string &accNumber){
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