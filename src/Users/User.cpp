/**
 * @file User.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "User.hpp"
#include "Customer.hpp"
#include "Employee.hpp"

/**
 * @brief Construct a new Banking:: User:: User object
 * 
 * @param id 
 * @param name 
 * @param password 
 * @param branch 
 * @param address 
 */
Banking::User::User(std::string &id, std::string &name, std::string &password, std::string &branch, std::string &address):
id{id}, name{name}, password{password}, branch{branch}, address{address}
{
}

/**
 * @brief 
 * 
 * @return int 
 */
std::string Banking::User::getId()
{
    return this->id;
}

/**
 * @brief 
 * 
 * @param id 
 */
void Banking::User::set(int &id)
{
    this->id=id ;
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Banking::User::getName()
{
    return this->name;
}

/**
 * @brief 
 * 
 * @param name 
 */
void Banking::User::setName(std::string &name)
{
    this->name = name;
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Banking::User::getPassword()
{
    return this->password;
}

/**
 * @brief 
 * 
 * @param password 
 */
void Banking::User::setPassword(std::string &password)
{
    this->password = password;
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Banking::User::getBranch()
{
    return this->branch;
}

/**
 * @brief 
 * 
 * @param branch 
 */
void Banking::User::setBranch(std::string &branch)
{
    this->branch = branch;
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Banking::User::getAddress()
{
    return this->address;
}

/**
 * @brief 
 * 
 * @param address 
 */
void Banking::User::setAddress(std::string &address)
{
    this->address = address;
}

/**
 * @brief 
 * 
 * @param id 
 * @param name 
 * @param password 
 * @param branch 
 * @param address 
 * @param designationOrAccountNumber 
 * @return std::shared_ptr<Banking::User> 
 */
std::shared_ptr<Banking::User> Banking::User::createUser(std::string &id, std::string &name, std::string &password, std::string &address, std::string &branch, std::string &designationOrAccountNumber){
    
        if (id[3] =='E')
        {
            return std::dynamic_pointer_cast<Banking::User>(std::make_shared<Banking::Employee>(id, name, password, branch, address, designationOrAccountNumber));
        }
        else if (id[3] == 'C')
        {
            return std::dynamic_pointer_cast<Banking::User>(std::make_shared<Banking::Customer>(id, name, password, branch, address, designationOrAccountNumber));
        }
        else
        {
            return nullptr;
        }
}
