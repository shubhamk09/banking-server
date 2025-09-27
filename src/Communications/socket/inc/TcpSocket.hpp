/**
 * @file TcpSocket.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief TCP Socket base class implementation
 * @version 0.1
 * @date 2023-08-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "ISocket.hpp"
#include <asio.hpp>
#include <memory>

namespace Communications {
namespace Socket {

/**
 * @brief TCP socket implementation using ASIO
 * 
 * This class provides TCP socket functionality for both client and server operations.
 * It uses the ASIO library for network operations and implements the ISocket interface.
 */
class TcpSocket : public ISocket {
public:
    /**
     * @brief Construct a new TCP socket
     * @param ioContext ASIO io_context for handling asynchronous operations
     */
    explicit TcpSocket(asio::io_context& ioContext);

    /**
     * @brief Construct a new TCP socket from an existing socket
     * @param ioContext ASIO io_context for handling asynchronous operations
     * @param socket An existing ASIO TCP socket to take ownership of
     */
    TcpSocket(asio::io_context& ioContext, asio::ip::tcp::socket socket);

    /**
     * @brief Destroy the TCP socket, closing the connection if open
     */
    ~TcpSocket() override;

    // ISocket implementation
    /**
     * @brief Connect to a remote TCP endpoint
     * @param host The hostname or IP address to connect to
     * @param port The port number to connect to
     * @throws std::runtime_error If connection fails or socket is in server mode
     */
    void connect(const std::string& host, uint16_t port) override;

    /**
     * @brief Close the TCP connection
     */
    void disconnect() override;

    /**
     * @brief Check if the TCP socket is connected
     * @return true if connected, false otherwise
     */
    bool isConnected() const override;

    /**
     * @brief Send data over the TCP connection
     * @param message The data to send
     * @return Number of bytes sent
     * @throws std::runtime_error If sending fails or socket is not connected
     */
    size_t send(const std::string& message) override;

    /**
     * @brief Receive data from the TCP connection
     * @param maxLength Maximum amount of data to receive
     * @return The received data as a string
     * @throws std::runtime_error If receiving fails or socket is not connected
     */
    std::string receive(size_t maxLength = 1024) override;

    /**
     * @brief Bind the socket to a port for listening (server mode)
     * @param port The port number to bind to
     * @throws std::runtime_error If binding fails or socket is already connected
     */
    void bind(uint16_t port) override;

    /**
     * @brief Start listening for incoming connections
     * @param backlog Maximum number of pending connections in the queue
     * @throws std::runtime_error If not in server mode or listening fails
     */
    void listen(int backlog = 10) override;

    /**
     * @brief Accept an incoming connection
     * @return A new TcpSocket instance for the accepted connection
     * @throws std::runtime_error If not in server mode or accepting fails
     */
    std::shared_ptr<ISocket> accept() override;

private:
    asio::io_context& ioContext_;
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::acceptor acceptor_;
    bool isServer_;
    bool connected_;
};

} // namespace Socket
} // namespace Communications
