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
#include <nlohmann/json.hpp>

/**
 * @brief Construct a new Banking:: Database Operations:: Database Operations object
 * 
 * @param connPtr 
 */
Banking::DatabaseOperations::DatabaseOperations()
{
    Banking::Logger::Init();
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
    std::vector<std::string> container;
    bool result = SendQuery(statement_string, &container);
    // TO DO: Result is unused as of now
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
bool Banking::DatabaseOperations::buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName){
    std::string searchById{tableName+"_id"};
    return buildUpdateQuery(colName, searchVal, updateVal, tableName, searchById);
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
bool Banking::DatabaseOperations::buildUpdateQuery(const std::string &colName, const std::string &searchVal, const std::string &updateVal, const std::string &tableName, const std::string &seearchOn){
    std::string statement_string = "UPDATE "+tableName+" SET "+colName+" = '"+updateVal+"' WHERE "+seearchOn+" = '"+searchVal+"'";
    BANKING_LOGGER_INFO("Executing command {}", statement_string);
    bool result = SendQuery(statement_string);

    return result;
}    

/**
 * @brief 
 * 
 * @param data 
 */
bool Banking::DatabaseOperations::buildInsertionQery(const nlohmann::json &data){
    bool result{false};
    std::string tableName = data.at("table");
    if (data.at("values").is_array())
    {    
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
        result = SendQuery(statement_string);
    }
    else
    {
        BANKING_LOGGER_ERROR("Values passed is not an array");
    }

    return result;
}

/**
 * @brief
 *
 * @param searchVal
 * @param tableName
 * @param seearchOn
 * @return std::string
 */
bool Banking::DatabaseOperations::buildDeleteQuery(const std::string &searchVal, const std::string &tableName, const std::string &seearchOn){
    std::string statement_string = "DELETE FROM "+tableName+" WHERE "+seearchOn+" = '"+searchVal+"'";
    BANKING_LOGGER_INFO("Executing command {}", statement_string);
    bool result = SendQuery(statement_string);

    return result;
}

bool Banking::DatabaseOperations::SendQuery(const std::string &query, std::vector<std::string>* container)
{
    BANKING_LOGGER_INFO("Executing command {}", query);
    ZMQRequest& requestorSocket = Banking::ZMQRequest::getInstance("tcp://localhost:5501");
    std::istringstream iss(query);
    std::string operation;
    iss >> operation;

    std::string reply = requestorSocket.request(query);
    nlohmann::json result = nlohmann::json::parse(reply);
    std::string status = result["status"];
    if (status == "error")
    {
        BANKING_LOGGER_ERROR("Error: {}", result["message"]);
        reply = "Failed";
    }
    else
    {
        BANKING_LOGGER_INFO("Query executed successfully");
        reply = "OK";
    }


    if (operation == "SELECT")
    {
        /*
        Select Operation will return multiple data
        So we need to push all the data in the container
        If the reply is empty, then it means no data is found
        */

        auto data = result["data"];
        if (data.is_array())
        {
            for (auto &&value : data)
            {
                container->push_back(value.dump());
            }
        }
        else
        {
            BANKING_LOGGER_ERROR("Data is not an array");
        }
    }

    if (status == "error")
    {
        return false;
    }

    return true;
}
