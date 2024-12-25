/**
 * @file Employee.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
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
Banking::Employee::Employee(const std::string &id, const std::string &name, const std::string &password, const std::string &branch, const std::string &address, const std::string &designation):
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
void Banking::Employee::setDesignation(const std::string &designation)
{
    this->designation = designation;
}