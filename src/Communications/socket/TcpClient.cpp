/**
 * @file TcpClient.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Implementation of TCP Client class
 * @version 0.1
 * @date 2023-08-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TcpClient.hpp"
#include "Logger.hpp"
#include <iostream>

namespace Communications {
namespace Socket {

TcpClient::TcpClient(asio::io_context& ioContext)
    : ioContext_(ioContext)
    , running_(false) {
    clientSocket_ = std::make_shared<TcpSocket>(ioContext_);
}

TcpClient::~TcpClient() {
    disconnect();
}

void TcpClient::connect(const std::string& host, uint16_t port,
                       std::function<void(const std::string&)> messageHandler) {
    messageHandler_ = messageHandler;
    
    try {
        BANKING_LOGGER_INFO("Connecting to {}:{}", host, port);
        clientSocket_->connect(host, port);
        running_ = true;
        
        // Start receive thread
        receiveThread_ = std::thread(&TcpClient::handleMessages, this);
        BANKING_LOGGER_INFO("Connected successfully");
        
    } catch (const std::exception& e) {
        BANKING_LOGGER_ERROR("Failed to connect: {}", e.what());
        throw;
    }
}

void TcpClient::disconnect() {
    if (running_) {
        BANKING_LOGGER_INFO("Disconnecting from server");
        running_ = false;
        
        try {
            // Send a goodbye message
            clientSocket_->send("CLOSE");
        } catch (const std::exception& e) {
            BANKING_LOGGER_INFO("Error sending goodbye message: {}", e.what());
        }
        
        if (receiveThread_.joinable()) {
            receiveThread_.join();
        }
        
        clientSocket_->disconnect();
        BANKING_LOGGER_INFO("Disconnected from server");
    }
}

bool TcpClient::sendMessage(const std::string& message) {
    try {
        if (isConnected()) {
            clientSocket_->send(message);
            BANKING_LOGGER_INFO("Message sent: {}", message);
            return true;
        }
    } catch (const std::exception& e) {
        BANKING_LOGGER_ERROR("Failed to send message: {}", e.what());
    }
    return false;
}

bool TcpClient::isConnected() const {
    return running_ && clientSocket_->isConnected();
}

void TcpClient::handleMessages() {
    while (running_) {
        try {
            auto message = clientSocket_->receive();
            if (!message.empty()) {
                messageHandler_(message);
                BANKING_LOGGER_INFO("Message received: {}", message);
            }
        } catch (const std::exception& e) {
            if (running_) {
                BANKING_LOGGER_ERROR("Receive error: {}", e.what());
                break;
            }
        }
    }
    running_ = false;
}

} // namespace Socket
} // namespace Communications
