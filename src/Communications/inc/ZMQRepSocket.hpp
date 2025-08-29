/**
 * @file ZMQRepSocket.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief ZeroMQ Reply Socket wrapper for banking system communications
 * @version 0.1
 * @date 2025-08-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include "IZMQSocket.hpp"
#include <zmq.hpp>
#include <string>

namespace Banking {

/**
 * @brief ZeroMQ Reply Socket implementation
 * 
 * This class wraps ZeroMQ's reply socket functionality, providing
 * a clean interface for receiving requests and sending replies
 * in the banking system's communication layer.
 */
class ZMQRepSocket : public IZMQSocket {
public:
    /**
     * @brief Construct a new ZMQRepSocket object
     * 
     * @param context Reference to the ZMQ context
     * @param bindAddress Address to bind the socket to (e.g., "tcp://localhost:5555")
     */
    ZMQRepSocket(zmq::context_t& context, const std::string& bindAddress);
    
    /**
     * @brief Send a message through the socket
     * 
     * @param msg Reference to the message to send
     * @param flags Send flags for the operation
     * @return true If the message was sent successfully
     * @return false If the send operation failed
     */
    bool send(zmq::message_t& msg, zmq::send_flags flags) override;
    
    /**
     * @brief Receive a message from the socket
     * 
     * @param msg Reference to store the received message
     * @param flags Receive flags for the operation
     * @return true If a message was received successfully
     * @return false If the receive operation failed
     */
    bool recv(zmq::message_t& msg, zmq::recv_flags flags) override;
    
private:
    zmq::socket_t socket; ///< The underlying ZMQ socket
};
} // namespace Banking
