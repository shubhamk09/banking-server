/**
 * @file CustomerOperations.cpp
 * @author Shbham Kalihari (shubhamkalihari09@gmail.com)
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
std::string Banking::CustomerOperations::getCustomerNameById(const std::string &cstId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Customer_name", cstId, "Customer")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerPasswordById(const std::string &cstId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Customer_password", cstId, "Customer")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerAccountById(const std::string &cstId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Customer_account", cstId, "Customer")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerAddressById(const std::string &cstId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Customer_address", cstId, "Customer")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerBranchById(const std::string &cstId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Customer_branch", cstId, "Customer")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param newName 
 */
void Banking::CustomerOperations::setCustomerNameById(const std::string &cstId, const std::string& newName){
    Banking::DatabaseOperations::buildUpdateQuery("Customer_name", cstId, newName, "Customer");
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param newPassword 
 */
void Banking::CustomerOperations::setCustomerPasswordById(const std::string &cstId, const std::string& newPassword){
    Banking::DatabaseOperations::buildUpdateQuery("Customer_password", cstId, newPassword, "Customer");
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param designation 
 */
void Banking::CustomerOperations::setCustomerAccountById(const std::string &cstId, const std::string newAccount){
    // Todo: check if the Account is available in the Account table or not
    Banking::DatabaseOperations::buildUpdateQuery("Customer_account", cstId, newAccount, "Customer");
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param newAddress 
 */
void Banking::CustomerOperations::setCustomerAddressById(const std::string &cstId, const std::string& newAddress){
    Banking::DatabaseOperations::buildUpdateQuery("Customer_address", cstId, newAddress, "Customer");
}

/**
 * @brief 
 * 
 * @param cstId 
 * @param branchId 
 */
void Banking::CustomerOperations::setCustomerBranchById(const std::string &cstId, const std::string &branchId){
    //Todo: branch should exist in branch table before updating the branch of the cutomer
    Banking::DatabaseOperations::buildUpdateQuery("Customer_branch", cstId, branchId, "Customer");
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
void Banking::CustomerOperations::deleteCustomer(const std::string &cstId){
    Banking::DatabaseOperations::buildDeleteQuery(cstId, "Customer", "Customer_id");
}