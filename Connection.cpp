/**
 * @file Connection.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Connection.hpp"

/**
 * @brief Construct a new Banking:: Connection:: Connection object
 * 
 */
Banking::Connection::Connection()
{
    int result = sqlite3_open(this->dataBaseName.c_str(), &this->DB);
    if (result != SQLITE_OK) {
      throw std::runtime_error("Failed to open database.");
    }

    std::cout << "Database opened successfully." << std::endl;
    
}
/**
 * @brief Destroy the Banking:: Connection:: Connection object
 * 
 */
Banking::Connection::~Connection()
{
    if (DB != nullptr) {
        sqlite3_close(DB);
        std::cout << "Database closed successfully." << std::endl;
    }
}



