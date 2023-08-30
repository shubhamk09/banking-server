/**
 * @file BranchOperations.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "BranchOperations.hpp"

/**
 * @brief Construct a new Banking:: Database Operations:: Branch Operations object
 * 
 * @param connPtr 
 */
Banking::BranchOperations::BranchOperations(connection_shptr &connPtr): Banking::DatabaseOperations{connPtr}
{
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchNameById(std::string &branchId){
    std::string colName = "Branch_name";
    std::string tableName = "Branch";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchCityById(std::string &branchId){
    std::string colName = "Branch_city";
    std::string tableName = "Branch";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchAddressById(std::string &branchId){
    std::string colName = "Branch_address";
    std::string tableName = "Branch";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchManagerById(std::string &branchId){
    std::string colName = "Branch_manager";
    std::string tableName = "Branch";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return true 
 * @return false 
 */
bool Banking::BranchOperations::isActiveBranch(std::string &branchId){
    std::string colName = "Branch_active";
    std::string tableName = "Branch";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName);
    if(statement_string == "ACTIVE"){
        return true;
    }
    return false;
}