/**
 * @file EmployeeOperations.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DatabaseOperations.hpp"

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
    std::string getEmployeeNameById(std::string &empId);
    std::string getEmployeePasswordById(std::string &empId);
    std::string getEmployeeDesignationById(std::string &empId);
    std::string getEmployeeAddressById(std::string &empId);
    std::string getEmployeeBranchById(std::string &empId);
    
};  

} // namespace Banking