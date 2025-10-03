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
#include "IZMQSocket.hpp"
#include "ZMQRepSocket.hpp"
#include <thread>
#include <iostream>
namespace Banking
{

ZMQReceive::ZMQReceive(const std::string &bindAddress):
    replierSocket(new ZMQRepSocket(ZMQContextManager::getInstance()->getContext(), bindAddress)), ownsSocket(true)
{
}

ZMQReceive::ZMQReceive(IZMQSocket* socket):
    replierSocket(socket), ownsSocket(false)
{
}

ZMQReceive::~ZMQReceive()
{
    if (ownsSocket && replierSocket) {
        delete replierSocket;
    }
}

// Get the Singleton instance
ZMQReceive& ZMQReceive::getInstance(const std::string &bindAddress) {
    static ZMQReceive instance(bindAddress);
    return instance;
} 

std::string ZMQReceive::receiveRequest()
{
    zmq::message_t request;
    replierSocket->recv(request, zmq::recv_flags::none);
    return std::string(static_cast<char*>(request.data()), request.size());
}

std::string ZMQReceive::reply(const std::string& requestMessage)
{
    zmq::message_t reply(requestMessage.data(), requestMessage.size());
    replierSocket->send(reply, zmq::send_flags::none);
    return requestMessage;
}

} // namespace Banking


