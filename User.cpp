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

/**
 * @brief Construct a new Banking:: User:: User object
 * 
 * @param id 
 * @param name 
 * @param password 
 * @param branch 
 * @param address 
 */
Banking::User::User(int &id, std::string &name, std::string &password, std::string &branch, std::string &address):
id{id}, name{name}, password{password}, branch{branch}, address{address}
{
}

/**
 * @brief 
 * 
 * @return int 
 */
int Banking::User::getId()
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