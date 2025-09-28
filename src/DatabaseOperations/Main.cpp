/**
 * @file Main.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Driver for DatabaseOperations services
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Dispatcher.hpp"
#include "DatabaseOperations.hpp"
#include "CustomerOperations.hpp"
#include "EmployeeOperations.hpp"
#include "AccountOperations.hpp"
#include "BranchOperations.hpp"
#include "ZMQReceive.hpp"

int main() {
    using namespace Banking;

    // Create shared DatabaseOperations instance
    auto dbOps = std::make_shared<DatabaseOperations>();

    // Create specific operations
    auto customerOps = std::make_shared<CustomerOperations>();
    auto employeeOps = std::make_shared<EmployeeOperations>();
    auto accountOps = std::make_shared<AccountOperations>();
    auto branchOps = std::make_shared<BranchOperations>();

    // Create and configure the dispatcher
    Dispatcher &dispatcher = Dispatcher::getInstance();
    dispatcher.registerOperation("Customer", customerOps);
    dispatcher.registerOperation("Employee", employeeOps);
    dispatcher.registerOperation("Account", accountOps);
    dispatcher.registerOperation("Branch", branchOps);
    
    /* 
        Example message 
        nlohmann::json message;
        message["Operation"] = "Account";
        message["OperationType"] = "get";
        message["ColumnName"] = "Account_balance";
        message["Data"] = nlohmann::json::array({"20230809MYS00101"});

        // Dispatch messages
        std::string response = dispatcher.dispatch(message["Operation"], message);
        std::cout << "Response: " << response << std::endl;

    */


    auto& zmqReceiver = ZMQReceive::getInstance("tcp://*:5502");

    std::cout << "Server is listening for incoming requests..." << std::endl;

    // Event loop to listen for incoming requests
    while (true) {
        // Receive a request from the client
        std::string request = zmqReceiver.receiveRequest();

        try {
            // Here you can process the request and generate a response
            nlohmann::json requestJson = nlohmann::json::parse(request);
            std::string operation = requestJson["Operation"];
            std::string response = dispatcher.dispatch(operation, requestJson);

            // Send the reply back to the client
            zmqReceiver.reply(response);
        } catch (const nlohmann::json::parse_error& e) {
            // Handle JSON parse errors gracefully
            nlohmann::json errorResponse;
            errorResponse["error"] = "Invalid JSON format";
            errorResponse["message"] = e.what();
            errorResponse["received"] = request;
            
            std::cout << "JSON Parse Error: " << e.what() << std::endl;
            std::cout << "Received message: '" << request << "'" << std::endl;
            
            zmqReceiver.reply(errorResponse.dump());
        } catch (const std::exception& e) {
            // Handle other errors gracefully
            nlohmann::json errorResponse;
            errorResponse["error"] = "Processing error";
            errorResponse["message"] = e.what();
            
            std::cout << "Processing Error: " << e.what() << std::endl;
            
            zmqReceiver.reply(errorResponse.dump());
        }
    }

    return 0;
}