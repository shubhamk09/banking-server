#include "inc/ZMQReqSocket.hpp"
#include "Logger.hpp"

namespace Banking {

ZMQReqSocket::ZMQReqSocket(zmq::context_t& context, const std::string& connectAddress)
    : socket(context, zmq::socket_type::req) {
    try {
        socket.connect(connectAddress);
    } catch (const zmq::error_t& e) {
        BANKING_LOGGER_ERROR("ZMQ Socket error: {}", e.what());
        throw;
    }
}

bool ZMQReqSocket::send(zmq::message_t& msg, zmq::send_flags flags) {
    try {
        return socket.send(msg, flags).has_value();
    } catch (const zmq::error_t& e) {
        BANKING_LOGGER_ERROR("ZMQ Send error: {}", e.what());
        return false;
    }
}

bool ZMQReqSocket::recv(zmq::message_t& msg, zmq::recv_flags flags) {
    try {
        return socket.recv(msg, flags).has_value();
    } catch (const zmq::error_t& e) {
        BANKING_LOGGER_ERROR("ZMQ Receive error: {}", e.what());
        return false;
    }
}

} // namespace Banking
