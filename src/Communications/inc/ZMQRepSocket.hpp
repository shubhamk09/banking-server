#pragma once
#include "IZMQSocket.hpp"
#include <zmq.hpp>
#include <string>

namespace Banking {
class ZMQRepSocket : public IZMQSocket {
public:
    ZMQRepSocket(zmq::context_t& context, const std::string& bindAddress);
    bool send(zmq::message_t& msg, zmq::send_flags flags) override;
    bool recv(zmq::message_t& msg, zmq::recv_flags flags) override;
private:
    zmq::socket_t socket;
};
} // namespace Banking
