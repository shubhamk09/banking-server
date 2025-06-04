/**
 * @file ZMQRecieve.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Header file for ZMQContextManager class
 * @version 0.1
 * @date 2025-06-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef ZMQRECEIVE_HPP
#define ZMQRECEIVE_HPP

#include "ZMQContextManager.hpp"

namespace Banking{

class ZMQReceive
{
private:
    zmq::socket_t replierSocket;
    ZMQReceive(const std::string& bindAddress);
    ~ZMQReceive();
public:

    // Delete copy constructor and assignment operator
    ZMQReceive(const ZMQReceive&) = delete;
    ZMQReceive& operator=(const ZMQReceive&) = delete;
    // Get the Singleton instance
    static ZMQReceive& getInstance(const std::string &bindAddress);

    std::string receiveRequest();
    std::string reply(const std::string& requestMessage);
};

} // namespace Banking
using reqlier_shptr = std::shared_ptr<Banking::ZMQReceive>;
#endif //ZMQRECEIVE_HPP