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
#include "spdlog/spdlog.h"
#include "Logger.hpp"
#include "EmployeeOperations.hpp"
#include "CustomerOperations.hpp"
#include "AccountOperations.hpp"
#include "BranchOperations.hpp"
#include "Employee.hpp"
#include "Customer.hpp"

int main(int argc, char** argv)
{
    
    try
    {
        // Initializing Logger
        // std::shared_ptr<Banking::Logger> logger = std::make_shared<Banking::Logger>();
        Banking::Logger::Init();
        Banking::connection_shptr ptr{std::make_shared<Banking::Connection>()};
        // Testing Employee
        Banking::Logger::GetLogger()->info("Testing Employee");
        std::shared_ptr<Banking::EmployeeOperations> dbO{std::make_shared<Banking::EmployeeOperations>(ptr)};
        std::string empid{"MYSE00101"};
        std::string name{dbO->getEmployeeNameById(empid)};
        std::string password{dbO->getEmployeePasswordById(empid)};
        std::string designation{dbO->getEmployeeDesignationById(empid)};
        std::string address{dbO->getEmployeeAddressById(empid)};
        std::string branch{dbO->getEmployeeBranchById(empid)};
        // Testing Branch
        Banking::Logger::GetLogger()->info("Testing Branch");
        std::shared_ptr<Banking::BranchOperations> db1{std::make_shared<Banking::BranchOperations>(ptr)};\
        std::cout<<db1->getBranchNameById(branch)<<std::endl;
        std::cout<<db1->getBranchCityById(branch)<<std::endl;
        std::cout<<db1->getBranchAddressById(branch)<<std::endl;
        std::cout<<db1->getBranchManagerById(branch)<<std::endl;
        std::cout<<db1->isActiveBranch(branch)<<std::endl;
        // Testing Customer
        Banking::Logger::GetLogger()->info("Testing Customer");
        std::shared_ptr<Banking::User> newUser {Banking::User::createUser(empid, name, password, address, branch, designation)};
        std::cout<<newUser->getName()<<std::endl;
        std::shared_ptr<Banking::CustomerOperations> db2{std::make_shared<Banking::CustomerOperations>(ptr)};
        empid = "MYSC00101";
        name = db2->getCustomerNameById(empid);
        password = db2->getCustomerPasswordById(empid);
        std::string account = db2->getCustomerAccountById(empid);
        address = db2->getCustomerAddressById(empid);
        branch = db2->getCustomerBranchById(empid);
        newUser = Banking::User::createUser(empid, name, password, address, branch, account);
        std::cout<<newUser->getName()<<std::endl;
        // Testing Accounts
        Banking::Logger::GetLogger()->info("Testing Accounts");
        std::shared_ptr<Banking::AccountOperations> db3{std::make_shared<Banking::AccountOperations>(ptr)};
        std::cout<<db3->getAccountBalanceById(account)<<std::endl;
        std::cout<<db3->getAccountTransactionsById(account)<<std::endl;
        std::cout<<db3->getAccountBranchById(account)<<std::endl;
        std::cout<<db3->isActiveAccount(account)<<std::endl;
        

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    
    return (0);
}