
/**
 * @file ZMQRequest.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief This class is reponsible for making ZMQ Request
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */#include "ZMQRequest.hpp"

namespace Banking
{
ZMQRequest::ZMQRequest(const std::string &bindAddress)
:   requestorSocket(ZMQContextManager::getInstance()->getContext(), zmq::socket_type::req)
{
    requestorSocket.connect(bindAddress);
}

// Get the Singleton instance
ZMQRequest& ZMQRequest::getInstance(const std::string &bindAddress) {
    static ZMQRequest instance(bindAddress);
    return instance;
}

std::string ZMQRequest::request(const std::string &requestMessage)
{
    zmq::message_t request(requestMessage.data(), requestMessage.size());
    requestorSocket.send(request, zmq::send_flags::none);

    zmq::message_t reply;
    requestorSocket.recv(reply);

    return std::string(static_cast<char*>(reply.data()), reply.size());
}

} // namespace Banking
