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
std::string Banking::EmployeeOperations::getEmployeeNameById(const std::string &empId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Employee_name", empId, "Employee")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeePasswordById(const std::string &empId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Employee_password", empId, "Employee")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeDesignationById(const std::string &empId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Employee_designation", empId, "Employee")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeAddressById(const std::string &empId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Employee_address", empId, "Employee")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeBranchById(const std::string &empId){
    std::vector<std::string> columnVals{Banking::DatabaseOperations::buildSelectionQuery("Branch_id", empId, "EmployeeToBranch", "Employee_id")};
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newName 
 */
void Banking::EmployeeOperations::setEmployeeNameById(const std::string &empId, const std::string &newName){
    Banking::DatabaseOperations::buildUpdateQuery("Employee_name", empId, newName, "Employee");
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newPassword 
 */
void Banking::EmployeeOperations::setEmployeePasswordById(const std::string &empId, const std::string &newPassword){
    Banking::DatabaseOperations::buildUpdateQuery("Employee_password", empId, newPassword, "Employee");
}

/**
 * @brief 
 * 
 * @param empId 
 * @param designation 
 */
void Banking::EmployeeOperations::setEmployeeDesignationById(const std::string &empId, const std::string &designation){

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
    
    Banking::DatabaseOperations::buildUpdateQuery("Employee_designation", empId, designation, "Employee");
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newAddress 
 */
void Banking::EmployeeOperations::setEmployeeAddressById(const std::string &empId, const std::string &newAddress){
    Banking::DatabaseOperations::buildUpdateQuery("Employee_address", empId, newAddress, "Employee");
}

/**
 * @brief 
 * 
 * @param empId 
 * @param branchId 
 */
void Banking::EmployeeOperations::setEmployeeBranchById(const std::string &empId, const std::string &branchId){
    // TO do: first check the branch id which we want to change is there in the branch table or not
    Banking::DatabaseOperations::buildUpdateQuery("Branch_id", empId, branchId, "EmployeeToBranch", "Employee_id");
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
void Banking::EmployeeOperations::deleteEmployee(const std::string &empId){
    Banking::DatabaseOperations::buildDeleteQuery(empId, "Employee", "Employee_id");
    Banking::DatabaseOperations::buildDeleteQuery(empId, "EmployeeToBranch", "Employee_id");
}