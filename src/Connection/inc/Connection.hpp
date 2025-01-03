/**
 * @file Connection.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BANKING_CONNECTION_HPP
#define BANKING_CONNECTION_HPP

#include <iostream>
#include <sqlite3.h>
#include <filesystem>
#include <fstream>
#include <regex>
#include <memory>

extern std::string osVariable;


namespace Banking{

class Connection
{
    
private:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    Connection(Connection&&) = delete;
    Connection& operator=(Connection&&) = delete;
public:
    Connection();
    ~Connection();
public:
    sqlite3* DB;
    void getAllEmployee();
    std::string getEmploeeByname();
};

using connection_shptr = std::shared_ptr<Connection>;



}// namespace Banking ends

#endif //BANKING_CONNECTION_HPP