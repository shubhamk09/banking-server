/**
 * @file ZMQContextManager.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Singleton ZeroMQ context manager for banking system communications
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

/**
 * @brief Singleton manager for ZeroMQ context
 * 
 * This class provides a thread-safe singleton pattern for managing
 * the ZeroMQ context across the banking system's communication layer.
 * It ensures only one context exists throughout the application lifecycle.
 */
class ZMQContextManager
{

public:
    /**
     * @brief Get the singleton instance of ZMQContextManager
     * 
     * @return ZMQContextManager* Pointer to the singleton instance
     */
    static ZMQContextManager* getInstance();
    
    /**
     * @brief Destructor - cleans up ZeroMQ context
     */
    ~ZMQContextManager();

    /**
     * @brief Get the ZeroMQ context
     * 
     * @return zmq::context_t& Reference to the ZMQ context
     */
    zmq::context_t& getContext();

private:
    /**
     * @brief Private constructor for singleton pattern
     */
    explicit ZMQContextManager();
    
    // Delete copy and move constructors/operators for singleton
    ZMQContextManager(const ZMQContextManager&) = delete;
    ZMQContextManager& operator=(const ZMQContextManager&) = delete;
    ZMQContextManager(ZMQContextManager&&) = delete;
    ZMQContextManager& operator=(ZMQContextManager&&) = delete;

    /* Member variables */
    static ZMQContextManager* m_zmqInstance; ///< Singleton instance pointer

    zmq::context_t m_context; ///< ZeroMQ context

    std::mutex m_zmqMutex; ///< Mutex for thread safety
};

}// namespace Banking ends

#endif //ZMQContextManager_HPP