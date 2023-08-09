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
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
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
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
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
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
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
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName);
    return statement_string;
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
    std::string statement_string = Banking::DatabaseOperations::buildSelectionQuery(colName, empId, tableName, searchOn);
    return statement_string;
}