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
#include "DatabaseOperations.hpp"
#include "Employee.hpp"

int main(int argc, char** argv)
{
    
    try
    {
        Banking::connection_shptr ptr{std::make_shared<Banking::Connection>()};
        Banking::DatabaseOperations dbO(ptr);
        std::string empid{"MYS00101"};
        std::string name{dbO.getEmployeeNameById(empid)};
        std::string password{dbO.getEmployeePasswordById(empid)};
        std::string designation{dbO.getEmployeeDesignationById(empid)};
        std::string address{dbO.getEmployeeAddressById(empid)};
        std::string branch{dbO.getEmployeeBranchById(empid)};
        std::shared_ptr<Banking::User> newUser = std::make_shared<Banking::Employee>(empid, name, password, designation, address, branch);
        std::cout<<newUser->getName()<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    
    return (0);
}