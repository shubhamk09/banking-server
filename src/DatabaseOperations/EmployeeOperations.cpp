/**
 * @file EmployeeOperations.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "EmployeeOperations.hpp"

/**
 * @brief Construct a new Banking:: Database Operations:: Employee Operations object
 * 
 * @param connPtr 
 */
Banking::EmployeeOperations::EmployeeOperations(connection_shptr &connPtr): Banking::DatabaseOperations{connPtr}
{
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeNameById(std::string &empId){
    std::string colName = "Employee_name";
    std::string tableName = "Employee";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName)};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeePasswordById(std::string &empId){
    std::string colName = "Employee_password";
    std::string tableName = "Employee";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName)};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeDesignationById(std::string &empId){
    std::string colName = "Employee_designation";
    std::string tableName = "Employee";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName)};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeAddressById(std::string &empId){
    std::string colName = "Employee_address";
    std::string tableName = "Employee";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName)};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeBranchById(std::string &empId){
    std::string colName = "Branch_id";
    std::string tableName = "EmployeeToBranch";
    std::string searchOn = "Employee_id";
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName, searchOn)};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newName 
 */
void Banking::EmployeeOperations::setEmployeeNameById(std::string &empId, std::string &newName){
    std::string colName = "Employee_name";
    std::string tableName = "Employee";
    Banking::DatabaseOperations::buildUpdateQuery(colName, empId, newName, tableName);
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newPassword 
 */
void Banking::EmployeeOperations::setEmployeePasswordById(std::string &empId, std::string &newPassword){
    std::string colName = "Employee_password";
    std::string tableName = "Employee";
    Banking::DatabaseOperations::buildUpdateQuery(colName, empId, newPassword, tableName);
}

/**
 * @brief 
 * 
 * @param empId 
 * @param designation 
 */
void Banking::EmployeeOperations::setEmployeeDesignationById(std::string &empId, std::string &designation){
    std::string colName = "Employee_designation";
    std::string tableName = "Employee";
    
    if (designation == "Manager")
    {
            std::string checkColName = "Employee_id";
            std::string checkTableName = "EmployeeToBranch";
            std::string checkSearchOn = "Branch_id";
            std::string searchOnBranchValue{getEmployeeBranchById(empId)};
            std::vector<std::string> employeeInBranch{Banking::DatabaseOperations::buildSelectionQuery(checkColName, searchOnBranchValue, checkTableName, checkSearchOn)};
            for (auto employee: employeeInBranch){
                std::cout<<employee<<std::endl;
                if (getEmployeeDesignationById(employee)=="Manager")
                {
                    BANKING_LOGGER_ERROR("Cannort assign Manager to {}",empId);
                    return;
                }
            }
            
            
            
    }
    
    Banking::DatabaseOperations::buildUpdateQuery(colName, empId, designation, tableName);
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newAddress 
 */
void Banking::EmployeeOperations::setEmployeeAddressById(std::string &empId, std::string &newAddress){
    std::string colName = "Employee_address";
    std::string tableName = "Employee";
    Banking::DatabaseOperations::buildUpdateQuery(colName, empId, newAddress, tableName);
}

/**
 * @brief 
 * 
 * @param empId 
 * @param branchId 
 */
void Banking::EmployeeOperations::setEmployeeBranchById(std::string &empId, std::string &branchId){
    // TO do: first check the branch id which we want to change is there in the branch table or not
    std::string colName = "Branch_id";
    std::string tableName = "EmployeeToBranch";
    std::string searchOn = "Employee_id";
    Banking::DatabaseOperations::buildUpdateQuery(colName, empId, branchId, tableName, searchOn);
}

/**
 * @brief 
 * 
 * @param empl 
 */
void Banking::EmployeeOperations::addEmployee(Banking::Employee &&empl){
    nlohmann::json EmployeeData;
    EmployeeData.emplace("table", "Employee");
    EmployeeData.emplace("values", nlohmann::json::array());
    nlohmann::json& employeeValues = EmployeeData["values"];
    employeeValues.emplace_back(empl.getId());
    employeeValues.emplace_back(empl.getName());
    employeeValues.emplace_back(empl.getPassword());
    employeeValues.emplace_back(empl.getDesignation());
    employeeValues.emplace_back(empl.getAddress());
    Banking::DatabaseOperations::buildInsertionQery(EmployeeData);
    nlohmann::json EmployeeToBranchData;
    EmployeeToBranchData.emplace("table", "EmployeeToBranch");
    EmployeeToBranchData.emplace("values", nlohmann::json::array());
    nlohmann::json& employeeToBranchValues = EmployeeToBranchData["values"];
    employeeToBranchValues.emplace_back(empl.getId());
    employeeToBranchValues.emplace_back(empl.getBranch());
    Banking::DatabaseOperations::buildInsertionQery(EmployeeToBranchData);
}

/**
 * @brief 
 * 
 * @param empId 
 */
void Banking::EmployeeOperations::deleteEmployee(std::string &empId){
    std::string tableName = "Employee";
    std::string searchOn = "Employee_id";
    Banking::DatabaseOperations::buildDeleteQuery(empId, tableName, searchOn);
    tableName = "EmployeeToBranch";
    Banking::DatabaseOperations::buildDeleteQuery(empId, tableName, searchOn);
}