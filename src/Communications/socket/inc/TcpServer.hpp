#pragma once

#include "TcpSocket.hpp"
#include <memory>
#include <functional>
#include <thread>
#include <atomic>

namespace Communications {
namespace Socket {

/**
 * @brief TCP Server class that handles multiple client connections
 */
class TcpServer {
public:
    /**
     * @brief Construct a new TCP Server
     * @param ioContext ASIO io_context for handling asynchronous operations
     * @param port Port number to listen on
     */
    TcpServer(asio::io_context& ioContext, uint16_t port);
    
    /**
     * @brief Destructor ensures clean shutdown
     */
    ~TcpServer();

    /**
     * @brief Start the server
     * @param messageHandler Callback function to handle received messages
     */
    void start(std::function<void(const std::string&, std::shared_ptr<ISocket>)> messageHandler);

    /**
     * @brief Stop the server
     */
    void stop();

private:
    /**
     * @brief Handle new client connections
     */
    void handleConnections();

    asio::io_context& ioContext_;
    std::shared_ptr<TcpSocket> serverSocket_;
    std::thread acceptThread_;
    std::atomic<bool> running_;
    std::function<void(const std::string&, std::shared_ptr<ISocket>)> messageHandler_;
    uint16_t port_;
};

} // namespace Socket
} // namespace Communications
