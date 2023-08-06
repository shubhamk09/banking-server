/**
 * @file driver.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "EmployeeOperations.hpp"
#include "CustomerOperations.hpp"
#include "Employee.hpp"
#include "Customer.hpp"

int main(int argc, char** argv)
{
    
    try
    {
        Banking::connection_shptr ptr{std::make_shared<Banking::Connection>()};
        std::shared_ptr<Banking::EmployeeOperations> dbO{std::make_shared<Banking::EmployeeOperations>(ptr)};
        std::string empid{"MYSE00101"};
        std::string name{dbO->getEmployeeNameById(empid)};
        std::string password{dbO->getEmployeePasswordById(empid)};
        std::string designation{dbO->getEmployeeDesignationById(empid)};
        std::string address{dbO->getEmployeeAddressById(empid)};
        std::string branch{dbO->getEmployeeBranchById(empid)};
        std::shared_ptr<Banking::User> newUser {Banking::User::createUser(empid, name, password, address, branch, designation)};
        std::cout<<newUser->getName()<<std::endl;
        std::shared_ptr<Banking::CustomerOperations> db1{std::make_shared<Banking::CustomerOperations>(ptr)};
        empid = "MYSC00101";
        name = db1->getCustomerNameById(empid);
        password = db1->getCustomerPasswordById(empid);
        std::string account = db1->getCustomerAccountById(empid);
        address = db1->getCustomerAddressById(empid);
        branch = db1->getCustomerBranchById(empid);
        newUser = Banking::User::createUser(empid, name, password, address, branch, account);
        std::cout<<newUser->getName()<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    
    return (0);
}