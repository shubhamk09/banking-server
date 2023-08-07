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
 * @param empId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchNameById(std::string &empId){
    std::string colName = "branch_name";
    std::string tableName = "Branches";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchCityById(std::string &empId){
    std::string colName = "branch_city";
    std::string tableName = "Branches";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchAddressById(std::string &empId){
    std::string colName = "branch_address";
    std::string tableName = "Branches";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchManagerById(std::string &empId){
    std::string colName = "branch_manager";
    std::string tableName = "Branches";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
}

bool Banking::BranchOperations::isActiveBranch(std::string &empId){
    std::string colName = "branch_active";
    std::string tableName = "Branches";
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    if(statement_string == "ACTIVE"){
        return true;
    }
    return false;
}