/**
 * @file EmployeeOperations.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
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
Banking::EmployeeOperations::EmployeeOperations()
    : dbOps(std::make_shared<DatabaseOperations>())
{
}

Banking::EmployeeOperations::EmployeeOperations(std::shared_ptr<IDatabaseOperations> dbOperations)
    : dbOps(std::move(dbOperations))
{
}

std::string Banking::EmployeeOperations::getEmployeeNameById(const std::string &empId){
    std::vector<std::string> columnVals = dbOps->buildSelectionQuery("Employee_name", empId, "Employee");
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeePasswordById(const std::string &empId){
    std::vector<std::string> columnVals = dbOps->buildSelectionQuery("Employee_password", empId, "Employee");
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeDesignationById(const std::string &empId){
    std::vector<std::string> columnVals = dbOps->buildSelectionQuery("Employee_designation", empId, "Employee");
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeAddressById(const std::string &empId){
    std::vector<std::string> columnVals = dbOps->buildSelectionQuery("Employee_address", empId, "Employee");
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @return std::string 
 */
std::string Banking::EmployeeOperations::getEmployeeBranchById(const std::string &empId){
    std::vector<std::string> columnVals = dbOps->buildSelectionQuery("Branch_id", empId, "EmployeeToBranch", "Employee_id");
    return columnVals.at(0);
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newName 
 */
void Banking::EmployeeOperations::setEmployeeNameById(const std::string &empId, const std::string &newName){
    dbOps->buildUpdateQuery("Employee_name", empId, newName, "Employee");
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newPassword 
 */
void Banking::EmployeeOperations::setEmployeePasswordById(const std::string &empId, const std::string &newPassword){
    dbOps->buildUpdateQuery("Employee_password", empId, newPassword, "Employee");
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
            std::vector<std::string> employeeInBranch = dbOps->buildSelectionQuery(checkColName, searchOnBranchValue, checkTableName, checkSearchOn);
            // Todo: If we are assigning a Manager some other role then we should also assign someone else as manager, so that manager will be unique
            for (auto employee: employeeInBranch){
                if (getEmployeeDesignationById(employee)=="Manager")
                {
                    BANKING_LOGGER_ERROR("Cannot assign Manager to {}",empId);
                    return;
                }
            }
    }
    
    dbOps->buildUpdateQuery("Employee_designation", empId, designation, "Employee");
}

/**
 * @brief 
 * 
 * @param empId 
 * @param newAddress 
 */
void Banking::EmployeeOperations::setEmployeeAddressById(const std::string &empId, const std::string &newAddress){
    dbOps->buildUpdateQuery("Employee_address", empId, newAddress, "Employee");
}

/**
 * @brief 
 * 
 * @param empId 
 * @param branchId 
 */
void Banking::EmployeeOperations::setEmployeeBranchById(const std::string &empId, const std::string &branchId){
    // TO do: first check the branch id which we want to change is there in the branch table or not
    // TO do: if the Employee is branch manager then, we should assign someone else as branch manager before changing the branch id
    dbOps->buildUpdateQuery("Branch_id", empId, branchId, "EmployeeToBranch", "Employee_id");
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
    dbOps->buildInsertionQery(EmployeeData);
    nlohmann::json EmployeeToBranchData;
    EmployeeToBranchData.emplace("table", "EmployeeToBranch");
    EmployeeToBranchData.emplace("values", nlohmann::json::array());
    nlohmann::json& employeeToBranchValues = EmployeeToBranchData["values"];
    employeeToBranchValues.emplace_back(empl.getId());
    employeeToBranchValues.emplace_back(empl.getBranch());
    dbOps->buildInsertionQery(EmployeeToBranchData);
}

/**
 * @brief 
 * 
 * @param empId 
 */
void Banking::EmployeeOperations::deleteEmployee(const std::string &empId){
    dbOps->buildDeleteQuery(empId, "Employee", "Employee_id");
    dbOps->buildDeleteQuery(empId, "EmployeeToBranch", "Employee_id");
}

nlohmann::json Banking::EmployeeOperations::processMessage(const nlohmann::json& message)
{
    std::string operationType = message.at("OperationType");
    std::string columnName = message.at("ColumnName");
    nlohmann::json data = message.at("Data");

    if (operationType == "get") {
        if (columnName == "Employee_name") {
            return getEmployeeNameById(data.at(0));
        } else if (columnName == "Employee_password") {
            return getEmployeePasswordById(data.at(0));
        } else if (columnName == "Employee_designation") {
            return getEmployeeDesignationById(data.at(0));
        } else if (columnName == "Employee_address") {
            return getEmployeeAddressById(data.at(0));
        } else if (columnName == "Branch_id") {
            return getEmployeeBranchById(data.at(0));
        }
    } else if (operationType == "set") {
        if (columnName == "Employee_name") {
            setEmployeeNameById(data.at(0), data.at(1));
        } else if (columnName == "Employee_password") {
            setEmployeePasswordById(data.at(0), data.at(1));
        } else if (columnName == "Employee_designation") {
            setEmployeeDesignationById(data.at(0), data.at(1));
        } else if (columnName == "Employee_address") {
            setEmployeeAddressById(data.at(0), data.at(1));
        } else if (columnName == "Branch_id") {
            setEmployeeBranchById(data.at(0), data.at(1));
        }
    } else if (operationType == "add") {
        Banking::Employee employee(data.at(0), data.at(1), data.at(2), data.at(3), data.at(4), data.at(5));
        addEmployee(std::move(employee));
        return "Employee added successfully";
    } else if (operationType == "delete") {
        deleteEmployee(data.at(0));
        return "Employee deleted successfully";
    }
    
    return "Operation was not successful";
    // Handle other operations or return an error message
    // TO-DO: return nlohmann::json::object({{"error", "Invalid operation type"}});
}