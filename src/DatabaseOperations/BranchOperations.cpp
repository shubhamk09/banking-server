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
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName)};
    return columnVals.at(0);
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
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName)};
    return columnVals.at(0);
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
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName)};
    return columnVals.at(0);
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
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName)};
    return columnVals.at(0);
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
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, branchId, tableName)};
    if(columnVals.at(0) == "ACTIVE"){
        return true;
    }
    return false;
}

/**
 * @brief 
 * 
 * @param branchId 
 * @param newName 
 */
void Banking::BranchOperations::setBranchNameById(std::string &branchId, std::string &newName){
    std::string colName = "Branch_name";
    std::string tableName = "Branch";
    Banking::DatabaseOperations::buildUpdateQuery(colName, branchId, newName, tableName);
}

/**
 * @brief 
 * 
 * @param branchId 
 * @param newCity 
 */
void Banking::BranchOperations::setBranchCityById(std::string &branchId, std::string &newCity){
    std::string colName = "Branch_city";
    std::string tableName = "Branch";
    Banking::DatabaseOperations::buildUpdateQuery(colName, branchId, newCity, tableName);
}

/**
 * @brief 
 * 
 * @param branchId 
 * @param newAdd 
 */
void Banking::BranchOperations::setBranchAddressById(std::string &branchId, std::string &newAdd){
    std::string colName = "Branch_address";
    std::string tableName = "Branch";
    Banking::DatabaseOperations::buildUpdateQuery(colName, branchId, newAdd, tableName);
}

/**
 * @brief 
 * 
 * @param branchId 
 * @param newBranchManagerId 
 */
void Banking::BranchOperations::setBranchManagerById(std::string &branchId, std::string &newBranchManagerId){
    std::string colName = "Branch_address";
    std::string tableName = "Branch";
    Banking::DatabaseOperations::buildUpdateQuery(colName, branchId, newBranchManagerId, tableName);
}

/**
 * @brief 
 * 
 * @param branchId 
 * @param newName 
 * @param newCity 
 * @param newAdd 
 * @param newBranchManagerId 
 */
void Banking::BranchOperations::addBranch(const std::string &branchId, const std::string &newName, const std::string &newCity, const std::string &newAdd, const std::string &newBranchManagerId){
    nlohmann::json BranchData;
    BranchData.emplace("table", "Branch");
    BranchData.emplace("values", nlohmann::json::array());
    nlohmann::json& branchValues = BranchData["values"];
    branchValues.emplace_back(branchId);
    branchValues.emplace_back(newName);
    branchValues.emplace_back(newCity);
    branchValues.emplace_back(newAdd);
    branchValues.emplace_back("ACTIVE");
    branchValues.emplace_back(newBranchManagerId);
    Banking::DatabaseOperations::buildInsertionQery(BranchData);
}
    

/**
 * @brief 
 * 
 * @param branchId 
 */
void Banking::BranchOperations::deleteBranch(std::string &branchId){
    std::string tableName = "Branch";
    std::string searchOn = "Branch_id";
    Banking::DatabaseOperations::buildDeleteQuery(branchId, tableName, searchOn);
}