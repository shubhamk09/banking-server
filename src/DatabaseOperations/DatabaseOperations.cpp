/**
 * @file DatabaseOperations.cpp
 * @author your name (you@domain.com)
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
std::string Banking::DatabaseOperations::buildSelectionQuery(std::string &colName, std::string &searchVal, std::string &tableName){
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
std::string Banking::DatabaseOperations::buildSelectionQuery(std::string &colName, std::string &searchVal, std::string &tableName, std::string &seearchOn){
    std::string statement_string = "SELECT "+colName+" from "+tableName+" WHERE "+seearchOn+" = '"+searchVal+"'";
    std::cout<<"Executing command "<<statement_string<<std::endl;
    char* messaggeError;
    std::string returnVal;
    int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), callbackName, static_cast<void*>(&returnVal), NULL);
    if (exit != SQLITE_OK) 
        {
        std::cerr << "Error while getting Data for "<<colName<<" in Table "<<tableName<<" for "<<searchVal<< std::endl;
        sqlite3_free(messaggeError);
        }
    std::cout<<"Data Retrival for "<<colName<<" in table "<<tableName<<" is successfull"<<std::endl;
    return returnVal;
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
    std::string* returnVal = static_cast<std::string*>(data);
    if (column_count >0 && column_values[0]!=nullptr)
    {
        *returnVal = std::string(column_values[0]);
    }
    else
    {
        *returnVal = "";
    }
    
    return 0;
} 