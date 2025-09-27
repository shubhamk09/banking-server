/**
 * @file ServerMain.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Main entry point for TCP server application
 * @version 0.1
 * @date 2023-08-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TcpServer.hpp"
#include "Logger.hpp"
#include <iostream>
#include <asio.hpp>

using namespace Communications::Socket;
using namespace Banking;

void handleClientMessage(const std::string& message, std::shared_ptr<ISocket> client) {
    BANKING_LOGGER_INFO("Received client message: {}", message);
    std::cout << "Client says: " << message << std::endl;
    // Echo back to client
    client->send("Server received: " + message);
}

int main() {
    try {
        // Initialize Banking logger
        Banking::Logger::Init();
        
        asio::io_context ioContext;
        
        // Create work guard to keep io_context running
        auto work = asio::make_work_guard(ioContext);
        TcpServer server(ioContext, 8080);
        
        BANKING_LOGGER_INFO("Starting server on port 8080");
        server.start(handleClientMessage);
        
        // Run the IO context
        ioContext.run();
        
    } catch (const std::exception& e) {
        BANKING_LOGGER_ERROR("Server error: {}", e.what());
        return 1;
    }
    
    return 0;
}
