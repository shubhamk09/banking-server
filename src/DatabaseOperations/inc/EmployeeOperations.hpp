/**
 * @file EmployeeOperations.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DatabaseOperations.hpp"
#include "Employee.hpp"

namespace Banking
{

class EmployeeOperations : public DatabaseOperations
{
public:
    EmployeeOperations(connection_shptr &connPtr);
    ~EmployeeOperations() = default;

    EmployeeOperations(const EmployeeOperations&) = default;
    EmployeeOperations& operator=(const EmployeeOperations&) = default;
    EmployeeOperations(EmployeeOperations&&) = default;
    EmployeeOperations& operator=(EmployeeOperations&&) = default;
public:
    std::string getEmployeeNameById(const std::string &empId);
    std::string getEmployeePasswordById(const std::string &empId);
    std::string getEmployeeDesignationById(const std::string &empId);
    std::string getEmployeeAddressById(const std::string &empId);
    std::string getEmployeeBranchById(const std::string &empId);
    void setEmployeeNameById(const std::string &empId, const std::string &newName);
    void setEmployeePasswordById(const std::string &empId, const std::string &newPassword);
    void setEmployeeDesignationById(const std::string &empId, const std::string &designation);
    void setEmployeeAddressById(const std::string &empId, const std::string &newAddress);
    void setEmployeeBranchById(const std::string &empId, const std::string &branchId);
    void addEmployee(Banking::Employee &&empl);
    void deleteEmployee(const std::string &empId);
    
};  

} // namespace Banking