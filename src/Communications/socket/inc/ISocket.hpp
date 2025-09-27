#pragma once

#include <string>
#include <memory>

namespace Communications {
namespace Socket {

/**
 * @brief Interface for socket communication
 * 
 * This interface defines the basic operations that all socket implementations
 * must support, including both client and server functionality.
 */
class ISocket {
public:
    /** @brief Virtual destructor for proper cleanup */
    virtual ~ISocket() = default;

    /**
     * @brief Connect to a remote host
     * @param host The host name or IP address to connect to
     * @param port The port number to connect to
     * @throws std::runtime_error If connection fails
     */
    virtual void connect(const std::string& host, uint16_t port) = 0;

    /**
     * @brief Disconnect from the remote host
     * @throws std::runtime_error If disconnection fails
     */
    virtual void disconnect() = 0;

    /**
     * @brief Check if the socket is currently connected
     * @return true if connected, false otherwise
     */
    virtual bool isConnected() const = 0;

    /**
     * @brief Send data through the socket
     * @param message The string message to send
     * @return The number of bytes sent
     * @throws std::runtime_error If sending fails or socket is not connected
     */
    virtual size_t send(const std::string& message) = 0;

    /**
     * @brief Receive data from the socket
     * @param maxLength Maximum length of data to receive (default: 1024)
     * @return The received data as a string
     * @throws std::runtime_error If receiving fails or socket is not connected
     */
    virtual std::string receive(size_t maxLength = 1024) = 0;

    /**
     * @brief Bind the socket to a specific port (server mode)
     * @param port The port number to bind to
     * @throws std::runtime_error If binding fails or socket is already connected
     */
    virtual void bind(uint16_t port) = 0;

    /**
     * @brief Start listening for incoming connections (server mode)
     * @param backlog Maximum length of the queue of pending connections
     * @throws std::runtime_error If listening fails or not in server mode
     */
    virtual void listen(int backlog = 10) = 0;

    /**
     * @brief Accept an incoming connection (server mode)
     * @return A new socket for the accepted connection
     * @throws std::runtime_error If accepting fails or not in server mode
     */
    virtual std::shared_ptr<ISocket> accept() = 0;
};

} // namespace Socket
} // namespace Communications
