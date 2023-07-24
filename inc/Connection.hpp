/**
 * @file Connection.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <sqlite3.h>
#include <fstream>
#include <memory>

namespace Banking{

class Connection
{
private:
    const std::string dataBaseName {"C:/Projects/banking-server/Banking_db.db"};

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