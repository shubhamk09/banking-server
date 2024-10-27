/**
 * @file Customer.cpp
 * @author Shbham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Customer.hpp"

/**
 * @brief Construct a new Banking:: Customer:: Customer object
 * 
 * @param id 
 * @param name 
 * @param password 
 * @param branch 
 * @param address 
 * @param accountNumber 
 */
Banking::Customer::Customer(const std::string &id, const std::string &name, const std::string &password, const std::string &branch, const std::string &address, const std::string &accountNumber):
Banking::User{id, name, password, branch, address}, accountNumber{accountNumber}
{
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Banking::Customer::getAccountNumber()
{
     return this->accountNumber;
}

/**
 * @brief 
 * 
 * @param accountNumber 
 */
void Banking::Customer::setAccountNumber(const std::string accountNumber)
{
    this->accountNumber = accountNumber;
}