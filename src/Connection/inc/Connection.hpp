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
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
    json executeQuery(const std::string& query);
    static int callbackName(void* data, int column_count, char** column_values, char** column_names);
public:
    sqlite3* DB;
};

using connection_shptr = std::shared_ptr<Connection>;



}// namespace Banking ends

#endif //BANKING_CONNECTION_HPP