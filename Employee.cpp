/**
 * @file Employee.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Employee.hpp"

/**
 * @brief Construct a new Banking:: Employee:: Employee object
 * 
 * @param id 
 * @param name 
 * @param password 
 * @param branch 
 * @param address 
 * @param designation 
 */
Banking::Employee::Employee(int &id, std::string &name, std::string &password, std::string &branch, std::string &address, std::string &designation):
Banking::User{id, name, password, branch, address}, designation{designation}
{
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Banking::Employee::getDesignation()
{
     return this->designation;
}

/**
 * @brief 
 * 
 * @param designation 
 */
void Banking::Employee::setDesignation(std::string designation)
{
    this->designation = designation;
}