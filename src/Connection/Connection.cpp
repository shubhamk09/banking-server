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

#ifdef _WIN32
    std::string osVariable = "Windows";
#elif __linux__
    std::string osVariable = "Linux";
#else
    std::string osVariable = "Unknown";
#endif

/**
 * @brief Construct a new Banking:: Connection:: Connection object
 * 
 */
Banking::Connection::Connection()
{
    std::string rootPath{std::filesystem::current_path().string()};
    std::regex pattern("^(.*?)(?=banking-server)");
    std::smatch matches;
    std::string resultPath;
    if (std::regex_search(rootPath, matches, pattern)) {
        resultPath = matches.str(1);
    }
    resultPath = resultPath+"banking-server/Banking.db";
    if (osVariable=="Unknown"){
        throw std::runtime_error("Unknown OS");
    }

    int result = sqlite3_open(resultPath.c_str(), &this->DB);
    if (result != SQLITE_OK) {
      throw std::runtime_error("Failed to open database");
    }
    BANKING_LOGGER_INFO("Database {} opened successfully", resultPath);  
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



