/**
 * @file TcpServer.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Implementation of TCP Server class
 * @version 0.1
 * @date 2025-09-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TcpServer.hpp"
#include "Logger.hpp"
#include <iostream>

namespace Communications {
namespace Socket {

TcpServer::TcpServer(asio::io_context& ioContext, uint16_t port)
    : ioContext_(ioContext)
    , serverSocket_(std::make_shared<TcpSocket>(ioContext))
    , running_(false)
    , messageHandler_(nullptr)
    , port_(port) {
}

TcpServer::~TcpServer() {
    stop();
}

void TcpServer::start(std::function<void(const std::string&, std::shared_ptr<ISocket>)> messageHandler) {
    messageHandler_ = messageHandler;
    
    try {
        serverSocket_->bind(port_);
        serverSocket_->listen();
        running_ = true;
        
        BANKING_LOGGER_INFO("Server listening on port {}", port_);
        
        // Start accept thread
        acceptThread_ = std::thread(&TcpServer::handleConnections, this);
        
    } catch (const std::exception& e) {
        BANKING_LOGGER_ERROR("Server failed to start: {}", e.what());
        throw;
    }
}

void TcpServer::stop() {
    if (running_) {
        BANKING_LOGGER_INFO("Stopping server...");
        running_ = false;
        if (acceptThread_.joinable()) {
            acceptThread_.join();
        }
        BANKING_LOGGER_INFO("Server stopped");
    }
}

void TcpServer::handleConnections() {
    while (running_) {
        try {
            BANKING_LOGGER_INFO("Waiting for client connection...");
            auto clientSocket = serverSocket_->accept();
            BANKING_LOGGER_INFO("New client connected");
            
            // Start a new thread to handle this client's messages
            std::thread([this, clientSocket]() {
                try {
                    while (running_) {
                        auto message = clientSocket->receive();
                        if (!message.empty()) {
                            messageHandler_(message, clientSocket);
                            BANKING_LOGGER_INFO("Processed message from client");
                        }
                    }
                } catch (const std::exception& e) {
                    std::string error_msg = e.what();
                    if (error_msg.find("Client disconnected") != std::string::npos) {
                        BANKING_LOGGER_INFO("Client disconnected normally");
                    } else {
                        BANKING_LOGGER_ERROR("Client connection error: {}", error_msg);
                    }
                }
            }).detach();
            
        } catch (const std::exception& e) {
            if (running_) { // Only log if not stopping intentionally
                BANKING_LOGGER_ERROR("Accept error: {}", e.what());
                // Brief pause to prevent CPU spinning if accept fails
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
}

} // namespace Socket
} // namespace Communications
