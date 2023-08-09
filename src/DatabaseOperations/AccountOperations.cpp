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
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, accountId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param accountId 
 * @return std::string 
 */
std::string Banking::AccountOperations::getAccountTransactionsById(std::string &accountId){
    std::string colName = "Account_transactions";
    std::string tableName = "Account";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, accountId, tableName);
    return statement_string;
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
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, accountId, tableName);
    return statement_string;
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
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, accountId, tableName);
    if(statement_string == "ACTIVE"){
        return true;
    }
    return false;
}