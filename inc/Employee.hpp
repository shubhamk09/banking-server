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
#include "User.hpp"
namespace Banking{
    class Employee: public User
    {
    private:
        std::string designation;

    public:
        Employee(std::string &id, std::string &name, std::string &password, std::string &branch, std::string &address, std::string &designation);
        ~Employee() = default;
        
        Employee(const Employee&) = default;
        Employee& operator=(const Employee&) = default;
        Employee(Employee&&) = default;
        Employee& operator=(Employee&&) = default;


        std::string getDesignation();
        void setDesignation(std::string designation);
    };
}

