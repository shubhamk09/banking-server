/**
 * @file ZMQComms.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ZMQCOMMS_HPP
#define ZMQCOMMS_HPP

#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <string>
#include <mutex>

namespace Banking{

class ZMQComms
{

public:
    static ZMQComms* getInstance();
    ~ZMQComms();
    // Public API for sending messages
    void sendMessage(const std::string& topic, const std::string& message);

    // Public API for receiving messages
    std::string receiveMessage();

private:
    explicit ZMQComms();
    ZMQComms(const ZMQComms&) = delete;
    ZMQComms& operator=(const ZMQComms&) = delete;
    ZMQComms(ZMQComms&&) = delete;
    ZMQComms& operator=(ZMQComms&&) = delete;

    /* Member variables */
    static ZMQComms* m_zmqInstance;

    // ZeroMQ context and sockets
    zmq::context_t context;
    zmq::socket_t publisher;
    zmq::socket_t subscriber;

    // Mutex for thread safety
    std::mutex zmqMutex;
};

}// namespace Banking ends

#endif //ZMQCOMMS_HPP