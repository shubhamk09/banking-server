#include "ZMQContextManager.hpp"
#include "Logger.hpp"

namespace Banking
{
    ZMQContextManager* ZMQContextManager::m_zmqInstance = nullptr; // Define the static member

    ZMQContextManager::ZMQContextManager()
    : m_context(1)
    {
        Banking::Logger::Init();
        BANKING_LOGGER_INFO("ZMQContextManager object created");
    }

    // Send a message

    ZMQContextManager::~ZMQContextManager()
    {
        BANKING_LOGGER_INFO("ZMQContextManager object destroyed");
    }

    zmq::context_t& ZMQContextManager::getContext()
    {
        return m_context;
    }

    ZMQContextManager* ZMQContextManager::getInstance()
    {
        if (m_zmqInstance == nullptr)
        {
            m_zmqInstance = new ZMQContextManager();
        }
        
        return m_zmqInstance;
    }

} // namespace Banking