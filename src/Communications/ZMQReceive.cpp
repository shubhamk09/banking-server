/**
 * @file ZMQReceive.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Class is responsible for receiving ZMQ request
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "ZMQReceive.hpp"
#include <thread>
#include <iostream>
namespace Banking
{

Banking::ZMQReceive::ZMQReceive(const std::string &bindAddress):
    replierSocket(ZMQContextManager::getInstance()->getContext(), zmq::socket_type::rep)
{
    replierSocket.bind(bindAddress);
}

Banking::ZMQReceive::~ZMQReceive()
{
    replierSocket.close();
}

// Get the Singleton instance
ZMQReceive& Banking::ZMQReceive::getInstance(const std::string &bindAddress) {
    static ZMQReceive instance(bindAddress);
    return instance;
} 

std::string ZMQReceive::receiveRequest()
{
    zmq::message_t request;
    zmq::recv_result_t ret = replierSocket.recv(request);
    if (ret.has_value() && (EAGAIN == ret.value()))
    {
        // msocket had nothing to read and recv() timed out
        std::cout << "No message received" << std::endl;
        return std::string();
    }
    std::string requestStr(static_cast<char*>(request.data()), request.size());
    
    // Process the request and prepare a reply
    std::cout << "Request recieved: " + requestStr << std::endl;

    return requestStr;
}

std::string Banking::ZMQReceive::reply(const std::string &requestMessage)
{
    zmq::message_t reply(requestMessage.data(), requestMessage.size());
    replierSocket.send(reply, zmq::send_flags::none);
    
    return requestMessage;
}
    
} // namespace Banking


