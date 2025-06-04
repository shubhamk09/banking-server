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
    // Initialize logger here!
    Banking::Logger::Init(); // or whatever your logger init function is
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

std::string Banking::Connection::executeQuery(const std::string &query)
{
    json result;
    char* messageError;
    std::vector<std::string> container;

    int exit = sqlite3_exec(DB, query.c_str(), callbackName, &container, &messageError);

    if (exit != SQLITE_OK) 
    {
        // Add error message to the result JSON
        result["status"] = "error";
        result["message"] = messageError ? std::string(messageError) : "Unknown error";
        sqlite3_free(messageError); // Free the error message
    }
    else
    {
        // Add success status and container data to the result JSON
        result["status"] = "success";
        result["data"] = container; // Add the container content to the JSON
        BANKING_LOGGER_INFO("Query executed successfully");
    }
    std::string resultString = result.dump();
    return resultString; // Return the result string
}


int Banking::Connection::callbackName(void* data, int column_count, char** column_values, char** column_names){
    auto &container = *static_cast<std::vector<std::string>*>(data);
    if (column_count >0 && column_values[0]!=nullptr)
    {
        container.push_back(column_values[0]);
    }
    else
    {
        container.push_back("NULL");
    }
    
    return 0;
}