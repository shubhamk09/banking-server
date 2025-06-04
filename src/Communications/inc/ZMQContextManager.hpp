/**
 * @file ZMQContextManager.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Header file for ZMQContextManager class
 * @version 0.1
 * @date 2025-03-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ZMQContextManager_HPP
#define ZMQContextManager_HPP

#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <string>
#include <mutex>

namespace Banking{

class ZMQContextManager
{

public:
    static ZMQContextManager* getInstance();
    ~ZMQContextManager();

    zmq::context_t& getContext();

private:
    explicit ZMQContextManager();
    ZMQContextManager(const ZMQContextManager&) = delete;
    ZMQContextManager& operator=(const ZMQContextManager&) = delete;
    ZMQContextManager(ZMQContextManager&&) = delete;
    ZMQContextManager& operator=(ZMQContextManager&&) = delete;

    /* Member variables */
    static ZMQContextManager* m_zmqInstance;

    // ZeroMQ context and sockets
    zmq::context_t m_context;

    // Mutex for thread safety
    std::mutex m_zmqMutex;
};

}// namespace Banking ends

#endif //ZMQContextManager_HPP