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
std::string Banking::BranchOperations::getBranchNameById(const std::string &branchId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Branch_name", branchId, "Branch")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchCityById(const std::string &branchId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Branch_city", branchId, "Branch")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchAddressById(const std::string &branchId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Branch_address", branchId, "Branch")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return std::string 
 */
std::string Banking::BranchOperations::getBranchManagerById(const std::string &branchId){
    //To Do: return branch manager name instead of ID
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Branch_manager", branchId, "Branch")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param branchId 
 * @return true 
 * @return false 
 */
bool Banking::BranchOperations::isActiveBranch(const std::string &branchId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Branch_active", branchId, "Branch")};
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
void Banking::BranchOperations::setBranchNameById(const std::string &branchId, const std::string &newName){
    Banking::DatabaseOperations::buildUpdateQuery("Branch_name", branchId, newName, "Branch");
}

/**
 * @brief 
 * 
 * @param branchId 
 * @param newCity 
 */
void Banking::BranchOperations::setBranchCityById(const std::string &branchId, const std::string &newCity){
    Banking::DatabaseOperations::buildUpdateQuery("Branch_city", branchId, newCity, "Branch");
}

/**
 * @brief 
 * 
 * @param branchId 
 * @param newAdd 
 */
void Banking::BranchOperations::setBranchAddressById(const std::string &branchId, const std::string &newAdd){
    Banking::DatabaseOperations::buildUpdateQuery("Branch_address", branchId, newAdd, "Branch");
}

/**
 * @brief 
 * 
 * @param branchId 
 * @param newBranchManagerId 
 */
void Banking::BranchOperations::setBranchManagerById(const std::string &branchId, const std::string &newBranchManagerId){
    Banking::DatabaseOperations::buildUpdateQuery("Branch_manager", branchId, newBranchManagerId, "Branch");
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
void Banking::BranchOperations::deleteBranch(const std::string &branchId){
    Banking::DatabaseOperations::buildDeleteQuery(branchId, "Branch", "Branch_id");
}