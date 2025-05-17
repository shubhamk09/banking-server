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
#include "IOperations.hpp"
#include "ZMQRequest.hpp"

/**
 * @brief Construct a new Banking:: Database Operations:: Database Operations object
 * 
 * @param connPtr 
 */
Banking::DatabaseOperations::DatabaseOperations()
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
    std::vector<std::string> container;

    // int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), callbackName, &container, &messageError);
    SendQuery(statement_string, &container);

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
    // int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), nullptr, nullptr, &messageError);
    SendQuery(statement_string);
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
        // int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), nullptr, nullptr, &messageError);
        SendQuery(statement_string);
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
    // int exit = sqlite3_exec(connPtr->DB, statement_string.c_str(), nullptr, nullptr, &messageError);
    SendQuery(statement_string);
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
void Banking::DatabaseOperations::SendQuery(const std::string &query, std::vector<std::string>* container)
{
    BANKING_LOGGER_INFO("Executing command {}", query);
    ZMQRequest& requestorSocket = Banking::ZMQRequest::getInstance("tcp://localhost:5555");
    char* messageError;
    // int exit = sqlite3_exec(connPtr->DB, query.c_str(), nullptr, nullptr, &messageError);
    std::istringstream iss(query);
    std::string operation;
    iss >> operation;

    std::string reply = requestorSocket.request(query);

    if (operation == "SELECT")
    {
        /*
        Select Operation will return multiple rows
        So we need to push all the rows in the container
        and return the reply as "OK" or "Failed"
        If the reply is empty, then it means no data is found
        */
        std::string selectReply = "Failed";
        std::istringstream iss(reply);
        std::string line;
        while (std::getline(iss, line)) {
            if (!line.empty()) {
                container->push_back(line);
                selectReply = "OK";
            }
        }

        reply = selectReply;
    }
    
    
    if (reply == "OK")
    {
        BANKING_LOGGER_INFO("{} is successfull", operation);
    }
    else
    {
        BANKING_LOGGER_ERROR("{} Failed",operation);
    }
}
