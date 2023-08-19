/**
 * @file Connection.cpp
 * @author your name (you@domain.com)
 * @brief Create a connection to sqlite3 database
 * @version 0.1
 * @date 2023-07-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Logger.hpp"
#include "Connection.hpp"

/**
 * @brief Construct a new Banking:: Connection:: Connection object
 * 
 */
Banking::Connection::Connection()
{
    int result = sqlite3_open(this->dataBaseName.c_str(), &this->DB);
    if (result != SQLITE_OK) {
      throw std::runtime_error("Failed to open database");
    }
    BANKING_LOGGER_INFO("Database {} opened successfully", this->dataBaseName);  
}
/**
 * @brief Destroy the Banking:: Connection:: Connection object
 * 
 */
Banking::Connection::~Connection()
{
    if (DB != nullptr) {
        sqlite3_close(DB);
        BANKING_LOGGER_INFO("Database {} Closed successfully", this->dataBaseName); 
    }
    BANKING_LOGGER_WARN("Database was not initialized");
}



