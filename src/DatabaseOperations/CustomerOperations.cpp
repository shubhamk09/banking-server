/**
 * @file CustomerOperations.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "CustomerOperations.hpp"

/**
 * @brief Construct a new Banking:: Database Operations:: Customer Operations object
 * 
 * @param connPtr 
 */
Banking::CustomerOperations::CustomerOperations(connection_shptr &connPtr): Banking::DatabaseOperations{connPtr}
{
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerNameById(std::string &cstId){
    std::string colName = "Customer_name";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, cstId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerPasswordById(std::string &cstId){
    std::string colName = "Customer_password";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, cstId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerAccountById(std::string &cstId){
    std::string colName = "Customer_account";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, cstId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerAddressById(std::string &cstId){
    std::string colName = "Customer_address";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, cstId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerBranchById(std::string &cstId){
    std::string colName = "Customer_branch";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, cstId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param newName 
 */
void Banking::CustomerOperations::setCustomerNameById(std::string &cstId, std::string& newName){
    std::string colName = "Customer_name";
    std::string tableName = "Customer";
    Banking::DatabaseOperations::buildUpdateQuery(colName, cstId, newName, tableName);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param newPassword 
 */
void Banking::CustomerOperations::setCustomerPasswordById(std::string &cstId, std::string& newPassword){
    std::string colName = "Customer_password";
    std::string tableName = "Customer";
    Banking::DatabaseOperations::buildUpdateQuery(colName, cstId, newPassword, tableName);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param designation 
 */
void Banking::CustomerOperations::setCustomerAccountById(std::string &cstId, std::string newAccount){
    // Todo: check if the Account is available in the Account table or not
    std::string colName = "Customer_account";
    std::string tableName = "Customer";
    Banking::DatabaseOperations::buildUpdateQuery(colName, cstId, newAccount, tableName);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param newAddress 
 */
void Banking::CustomerOperations::setCustomerAddressById(std::string &cstId, std::string& newAddress){
    std::string colName = "Customer_address";
    std::string tableName = "Customer";
    Banking::DatabaseOperations::buildUpdateQuery(colName, cstId, newAddress, tableName);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param branchId 
 */
void Banking::CustomerOperations::setCustomerBranchById(std::string &cstId, std::string &branchId){
    //Todo: branch should exist in branch table before updating the branch of the cutomer
    std::string colName = "Customer_branch";
    std::string tableName = "Customer";
    Banking::DatabaseOperations::buildUpdateQuery(colName, cstId, branchId, tableName);
}

/**
 * @brief 
 * 
 * @param cust 
 */
void Banking::CustomerOperations::addCustomer(Banking::Customer &&cust){
    //Todo: call Accounts buildInsertionQuery to create account
    nlohmann::json CustomerData;
    CustomerData.emplace("table", "Customer");
    CustomerData.emplace("values", nlohmann::json::array());
    nlohmann::json& CustomerValues = CustomerData["values"];
    CustomerValues.emplace_back(cust.getId());
    CustomerValues.emplace_back(cust.getName());
    CustomerValues.emplace_back(cust.getPassword());
    CustomerValues.emplace_back(cust.getAccountNumber());
    CustomerValues.emplace_back(cust.getAddress());
    CustomerValues.emplace_back(cust.getBranch());
    Banking::DatabaseOperations::buildInsertionQery(CustomerData);
}

/**
 * @brief 
 * 
 * @param cstId 
 */
void Banking::CustomerOperations::deleteCustomer(std::string &cstId){
    std::string tableName = "Customer";
    std::string searchOn = "Customer_id";
    Banking::DatabaseOperations::buildDeleteQuery(cstId, tableName, searchOn);
    tableName = "CustomerToBranch";
    Banking::DatabaseOperations::buildDeleteQuery(cstId, tableName, searchOn);
}