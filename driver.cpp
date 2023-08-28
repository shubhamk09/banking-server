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
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(int argc, char** argv)
{
    
    try
    {
        json jsonString1 = R"({
            "pi": 3.141,
            "happy": true,
            "name": "Niels",
            "nothing": null,
            "answer": {
                "everything": 42
            },
            "list": [1, 0, 2],
            "object": {
                "currency": "USD",
                "value": 42.99
            }
        })"_json;
        
        // json jsonString2 = R"({
        //     "table": "Employee",
        //     "values: ["MYSE00102", "Shubham Kalihar", "Shannu", "accountant", "Ammana Mane"]
        // })"_json;
        std::cout<<jsonString1.dump()<<std::endl;
        // Initializing Logger
        // std::shared_ptr<Banking::Logger> logger = std::make_shared<Banking::Logger>();
        Banking::Logger::Init();
        Banking::connection_shptr ptr{std::make_shared<Banking::Connection>()};
        // Testing Employee
        BANKING_LOGGER_INFO("Testing Employee");
        std::shared_ptr<Banking::EmployeeOperations> dbO{std::make_shared<Banking::EmployeeOperations>(ptr)};
        std::string empid{"MYSE00101"};
        std::string name{dbO->getEmployeeNameById(empid)};
        std::string password{dbO->getEmployeePasswordById(empid)};
        std::string designation{dbO->getEmployeeDesignationById(empid)};
        std::string address{dbO->getEmployeeAddressById(empid)};
        std::string branch{dbO->getEmployeeBranchById(empid)};
        //Changing employee name
        BANKING_LOGGER_INFO("Testing Changing Employee Name");
        //Adding employee
        std::string empid2{"MYSE00102"};
        std::string name2{"Shubham Kalihari"};
        std::string password2{"Shannu"};
        std::string designation2{"Cashier"};
        std::string address2{"Shivmoga"};
        std::string branch2{"MYS001"};
        Banking::Employee newEmployee {empid2, name2, password2, branch2, address2, designation2};
        dbO->addEmployee(std::move(newEmployee));
        dbO->deleteEmployee(empid2);
        // Banking::Employee neEmpl{"MYSE00102", "Shubham Kalihari", "Shannu", "MYS001", "Varsha Enclave", "Cashier"};
        std::string newName {"Shubha ND"};
        dbO->setEmployeeNameById(empid, newName);
        std::cout<<"new name "<<dbO->getEmployeeNameById(empid)<<std::endl;
        // Testing Branch
        BANKING_LOGGER_INFO("Testing Branch");
        std::shared_ptr<Banking::BranchOperations> db1{std::make_shared<Banking::BranchOperations>(ptr)};\
        std::cout<<db1->getBranchNameById(branch)<<std::endl;
        std::cout<<db1->getBranchCityById(branch)<<std::endl;
        std::cout<<db1->getBranchAddressById(branch)<<std::endl;
        std::cout<<db1->getBranchManagerById(branch)<<std::endl;
        std::cout<<db1->isActiveBranch(branch)<<std::endl;
        // Testing Customer
        BANKING_LOGGER_INFO("Testing Customer");
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
        BANKING_LOGGER_INFO("Testing Accounts");
        std::shared_ptr<Banking::AccountOperations> db3{std::make_shared<Banking::AccountOperations>(ptr)};
        std::cout<<db3->getAccountBalanceById(account)<<std::endl;
        std::cout<<db3->getAccountTransactionsById(account)<<std::endl;
        std::cout<<db3->getAccountBranchById(account)<<std::endl;
        std::cout<<db3->isActiveAccount(account)<<std::endl;
        

    }
    catch(const std::exception& e)
    {
        BANKING_LOGGER_ERROR("{}", e.what());
    }
    
    
    return (0);
}