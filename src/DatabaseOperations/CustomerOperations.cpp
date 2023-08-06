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
 * @param empId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerNameById(std::string &empId){
    std::string colName = "Customer_name";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerPasswordById(std::string &empId){
    std::string colName = "Customer_password";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerAccountById(std::string &empId){
    std::string colName = "Customer_account";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerAddressById(std::string &empId){
    std::string colName = "Customer_account";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::CustomerOperations::getCustomerBranchById(std::string &empId){
    std::string colName = "Customer_branch";
    std::string tableName = "Customer";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}