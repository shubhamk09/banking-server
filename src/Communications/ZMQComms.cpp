#include "ZMQComms.hpp"
#include "Logger.hpp"

namespace Banking
{
    ZMQComms* ZMQComms::m_zmqInstance = nullptr; // Define the static member

    ZMQComms::ZMQComms()
    : context(1), publisher(context, zmq::socket_type::pub), subscriber(context, zmq::socket_type::sub)
    {
        Banking::Logger::Init();
        BANKING_LOGGER_INFO("ZMQComms object created");
        // Bind publisher to a known endpoint
        publisher.bind("tcp://127.0.0.1:5555");

        // Connect subscriber to the same endpoint
        subscriber.connect("tcp://127.0.0.1:5555");
        subscriber.set(zmq::sockopt::subscribe, ""); // Subscribe to all topics
    }

    // Send a message
    void ZMQComms::sendMessage(const std::string& topic, const std::string& message) {
        std::lock_guard<std::mutex> lock(zmqMutex);

        zmq::message_t topicMsg(topic.data(), topic.size());
        zmq::message_t messageMsg(message.data(), message.size());

        publisher.send(topicMsg, zmq::send_flags::sndmore);
        publisher.send(messageMsg, zmq::send_flags::none);
    }

    // Receive a message
    std::string ZMQComms::receiveMessage() {
        std::lock_guard<std::mutex> lock(zmqMutex);

        zmq::message_t topicMsg;
        zmq::message_t messageMsg;

        (void)subscriber.recv(topicMsg, zmq::recv_flags::none);
        (void)subscriber.recv(messageMsg, zmq::recv_flags::none);

        return messageMsg.to_string();
    }

    ZMQComms::~ZMQComms()
    {
        BANKING_LOGGER_INFO("ZMQComms object destroyed");
    }

    ZMQComms* ZMQComms::getInstance()
    {
        if (m_zmqInstance == nullptr)
        {
            m_zmqInstance = new ZMQComms();
        }
        
        return m_zmqInstance;
    }

} // namespace Banking