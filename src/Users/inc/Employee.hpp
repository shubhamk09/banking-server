/**
 * @file Employee.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BANKING_EMPLOYEE_HPP
#define BANKING_EMPLOYEE_HPP

#include "User.hpp"
namespace Banking{
    class Employee: public User
    {
    private:
        std::string designation;

    public:
        Employee(const std::string &id, const std::string &name, const std::string &password, const std::string &branch, const std::string &address, const std::string &designation);
        ~Employee() = default;
        
        Employee(const Employee&) = default;
        Employee& operator=(const Employee&) = default;
        Employee(Employee&&) = default;
        Employee& operator=(Employee&&) = default;


        std::string getDesignation();
        void setDesignation(const std::string &designation);
    };
}
#endif //BANKING_EMPLOYEE_HPP

