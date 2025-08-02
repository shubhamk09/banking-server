/**
 * @file IZMQSocket.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Interface for ZeroMQ socket implementations in banking system
 * @version 0.1
 * @date 2025-08-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include <zmq.hpp>

namespace Banking {

/**
 * @brief Interface for ZeroMQ socket implementations
 * 
 * This interface defines the common operations that all ZMQ socket
 * implementations must provide for the banking system's communication layer.
 */
class IZMQSocket {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~IZMQSocket() = default;
    
    /**
     * @brief Send a message through the socket
     * 
     * @param msg Reference to the message to send
     * @param flags Send flags for the operation
     * @return true If the message was sent successfully
     * @return false If the send operation failed
     */
    virtual bool send(zmq::message_t& msg, zmq::send_flags flags) = 0;
    
    /**
     * @brief Receive a message from the socket
     * 
     * @param msg Reference to store the received message
     * @param flags Receive flags for the operation
     * @return true If a message was received successfully
     * @return false If the receive operation failed
     */
    virtual bool recv(zmq::message_t& msg, zmq::recv_flags flags) = 0;
};
} // namespace Banking
