/**
 * @file DatabaseOperations.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DatabaseOperations.hpp"

/**
 * @brief Construct a new Banking:: Database Operations:: Database Operations object
 * 
 * @param connPtr 
 */
Banking::DatabaseOperations::DatabaseOperations(connection_shptr &connPtr):connPtr{connPtr}
{
}

/**
 * @brief 
 * 
 * @param colName 
 * @param searchVal 
 * @param tableName 
 * @return std::string 
 */
std::vector<std::string> Banking::DatabaseOperations::buildSelectionQuery(const std::string &colName, const std::string &searchVal, const std::string &tableName){
    std::string searchById{tableName+"_id"};
    return buildSelectionQuery(colName, searchVal, tableName, searchById);
}

/** 
 * @brief
 * 
 * @param colName 
 * @param searchVal 
 * @param tableName 
 * @param seearchOn 
 * @return std::string 
 */
std::vector<std::string> Banking::DatabaseOperations::buildSelectionQuery(const std::string &colName, const std::string &searchVal, const std::string &tableName, const std::string &seearchOn){
    std::string statement_string = "SELECT "+colName+" from "+tableName+" WHERE "+seearchOn+" = '"+searchVal+"'";
    BANKING_LOGGER_INFO("Executing command {}", statement_string);
    char* messageError;
    std::string returnVal;
    std::vector<std::string> container;
    // int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), callbackName, static_cast<void*>(&returnVal), &messageError);
    int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), callbackName, &container, &messageError);
    if (exit != SQLITE_OK) 
    {
        BANKING_LOGGER_ERROR("Error while getting Data for {} in Table {} for {}", colName, tableName, searchVal);
        sqlite3_free(messageError);
    }
    else
    {
        BANKING_LOGGER_INFO("Data Retrival for {} in table {} is successfull", colName, tableName);
    }
    return container;
}

/**
 * @brief 
 * 
 * @param colName 
 * @param searchVal 
 * @param updateVal 
 * @param tableName 
 * @return std::string 
 */
void Banking::DatabaseOperations::buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName){
    std::string searchById{tableName+"_id"};
    buildUpdateQuery(colName, searchVal, updateVal, tableName, searchById);
}

/**
 * @brief 
 * 
 * @param colName 
 * @param searchVal 
 * @param updateVal 
 * @param tableName 
 * @param seearchOn 
 * @return std::string 
 */
void Banking::DatabaseOperations::buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName, const std::string &seearchOn){
    std::string statement_string = "UPDATE "+tableName+" SET "+colName+" = '"+updateVal+"' WHERE "+seearchOn+" = '"+searchVal+"'";
    BANKING_LOGGER_INFO("Executing command {}", statement_string);
    char* messageError;
    int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK) 
    {
        BANKING_LOGGER_ERROR("Error while setting Data for {} in Table {} for {}", colName, tableName, searchVal);
        sqlite3_free(messageError);
    }
    else
    {
        BANKING_LOGGER_INFO("Data updation for {} in table {} is successfull", colName, tableName);
    }
}    

/**
 * @brief 
 * 
 * @param data 
 */
void Banking::DatabaseOperations::buildInsertionQery(const nlohmann::json &data){
    // json jsonString1 = R"({
    //         "table": "Employee",
    //         "values": ["str1", "str2", "str3"]
    //     })"_json;
    std::string tableName = data.at("table");
    if (data.at("values").is_array())
    {    
        int arraySize{static_cast<int>(data.at("values").size())};
        std::string statement_string = "INSERT INTO '"+tableName+"' VALUES (";
        for (auto &&value : data.at("values"))
        {
            statement_string += value.dump()+", ";
        }
        // Remove last comma
        std::size_t lastCommaPos{statement_string.rfind(',')};
        if (lastCommaPos != std::string::npos)
        {
            statement_string = statement_string.substr(0, lastCommaPos)+");";
        }
        BANKING_LOGGER_INFO("Executing command {}", statement_string);
        char* messageError;
        int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), nullptr, nullptr, &messageError);
        if (exit != SQLITE_OK) 
        {
            BANKING_LOGGER_ERROR("Error while inserting Data in Table {}",tableName);
            sqlite3_free(messageError);
        }
        else
        {
            BANKING_LOGGER_INFO("Data Insertion in table {} is successfull", tableName);
        }
    }
    else
    {
        BANKING_LOGGER_ERROR("Values passed is not an array");
    }
    
}

/**
 * @brief 
 * 
 * @param searchVal 
 * @param tableName 
 * @param seearchOn 
 * @return std::string 
 */
void Banking::DatabaseOperations::buildDeleteQuery(const std::string &searchVal, const std::string &tableName, const std::string &seearchOn){
    std::string statement_string = "DELETE FROM "+tableName+" WHERE "+seearchOn+" = '"+searchVal+"'";
    BANKING_LOGGER_INFO("Executing command {}", statement_string);
    char* messageError;
    int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK) 
    {
        BANKING_LOGGER_ERROR("Error while deleting Data in Table {} for {}", tableName, searchVal);
        sqlite3_free(messageError);
    }
    else
    {
        BANKING_LOGGER_INFO("Data deletion from table {} is successfull", tableName);
    }
}

/**
 * @brief 
 * 
 * @param data 
 * @param column_count 
 * @param column_values 
 * @param column_names 
 * @return int 
 */
int Banking::DatabaseOperations::callbackName(void* data, int column_count, char** column_values, char** column_names){
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