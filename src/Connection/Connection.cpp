/**
 * @file Connection.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
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
    std::string rootPath{std::filesystem::current_path().string()};
    std::regex pattern("^(.*banking-server)");
    std::smatch matches;
    std::string resultPath;

    // Search for the 'banking-server' part in the current path
    if (std::regex_search(rootPath, matches, pattern) && matches.size() > 0) {
        // The first match will give the correct path up to 'banking-server'
        resultPath = matches.str(1) + "/Banking.db";
    } else {
        throw std::runtime_error("Failed to find 'banking-server' in path");
    }

    if (!std::filesystem::exists(resultPath)) {
        throw std::runtime_error("Database file not found at " + resultPath);
    }

    int result = sqlite3_open(resultPath.c_str(), &this->DB);
    if (result != SQLITE_OK) {
        throw std::runtime_error("Failed to open database at " + resultPath);
    } else {
        BANKING_LOGGER_INFO("Database {} opened successfully", resultPath);
    }
}
/**
 * @brief Destroy the Banking:: Connection:: Connection object
 * 
 */
Banking::Connection::~Connection()
{
    if (DB != nullptr) {
        sqlite3_close(DB);
        BANKING_LOGGER_INFO("Database Closed successfully"); 
    }
    else{
        BANKING_LOGGER_WARN("Database was not initialized");
    }
    
}



