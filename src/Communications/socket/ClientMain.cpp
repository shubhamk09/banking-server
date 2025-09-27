/**
 * @file ClientMain.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Main entry point for TCP client application
 * @version 0.1
 * @date 2023-08-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TcpClient.hpp"
#include "Logger.hpp"
#include <iostream>
#include <asio.hpp>

using namespace Communications::Socket;
using namespace Banking;

void handleServerMessage(const std::string& message) {
    std::cout << "Received from server: " << message << std::endl;
}

int main() {
    try {
        // Initialize Banking logger
        Banking::Logger::Init();
        
        asio::io_context ioContext;
        
        // Create work guard to keep io_context running
        auto work = asio::make_work_guard(ioContext);
        TcpClient client(ioContext);
        
        // Connect to server
        client.connect("localhost", 8080, handleServerMessage);
        
        // Start a thread to run the IO context
        std::thread ioThread([&ioContext]() {
            ioContext.run();
        });
        
        std::cout << "\nEnter messages to send (type 'quit' to exit):\n" << std::endl;
        
        // Main loop for sending messages
        std::string message;
        while (client.isConnected()) {
            std::cout << "> ";
            std::getline(std::cin, message);
            
            if (message == "quit") {
                BANKING_LOGGER_INFO("User requested quit");
                break;
            }
            
            if (!message.empty()) {
                if (!client.sendMessage(message)) {
                    BANKING_LOGGER_ERROR("Failed to send message");
                    break;
                }
            }
        }
        
        // Clean shutdown
        client.disconnect();
        work.reset();  // Allow io_context to stop
        ioContext.stop();
        if (ioThread.joinable()) {
            ioThread.join();
        }
        
        BANKING_LOGGER_INFO("Client shutdown complete");
        
    } catch (const std::exception& e) {
        BANKING_LOGGER_ERROR("Client error: {}", e.what());
        return 1;
    }
    
    return 0;
}
