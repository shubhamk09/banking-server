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
 * @param empId 
 * @return std::string 
 */

std::string Banking::DatabaseOperations::getEmployeeNameById(std::string &empId){
    std::string statement_string = "SELECT Employee_name from Employee WHERE Employee_id = 'MYS00101'";
    char* messaggeError;
    std::string returnVal;
    int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), callbackName, static_cast<void*>(&returnVal), NULL);
    if (exit != SQLITE_OK) 
        {
        std::cerr << "Error in SELECT statement" << std::endl;
        sqlite3_free(messaggeError);
        }
    else
        {
        std::cout << "Records created Successfully!" << std::endl;
        }

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
        *returnVal = column_values[0];
    }
    else
    {
        *returnVal = "";
    }
    
    return 0;
} 