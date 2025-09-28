/**
 * @file TcpClient.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief TCP Client interface for banking system
 * @version 0.1
 * @date 2023-08-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "TcpSocket.hpp"
#include <memory>
#include <functional>
#include <thread>
#include <atomic>

namespace Communications {
namespace Socket {

/**
 * @brief TCP Client class for handling socket connections
 */
class TcpClient {
public:
    /**
     * @brief Construct a new TCP Client
     * @param ioContext ASIO io_context for handling asynchronous operations
     */
    explicit TcpClient(asio::io_context& ioContext);
    
    /**
     * @brief Destructor ensures clean disconnect
     */
    ~TcpClient();

    /**
     * @brief Connect to a server
     * @param host Server hostname or IP address
     * @param port Server port number
     * @param messageHandler Callback function to handle received messages
     */
    void connect(const std::string& host, uint16_t port,
                std::function<void(const std::string&)> messageHandler);

    /**
     * @brief Disconnect from the server
     */
    void disconnect();

    /**
     * @brief Send a message to the server
     * @param message Message to send
     * @return true if message was sent successfully
     */
    bool sendMessage(const std::string& message);

    /**
     * @brief Check if client is connected
     * @return true if connected to server
     */
    bool isConnected() const;

private:
    /**
     * @brief Handle incoming messages
     */
    void handleMessages();

    asio::io_context& ioContext_;
    std::shared_ptr<TcpSocket> clientSocket_;
    std::thread receiveThread_;
    std::atomic<bool> running_;
    std::function<void(const std::string&)> messageHandler_;
};

} // namespace Socket
} // namespace Communications
