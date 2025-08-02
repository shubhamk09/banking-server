#pragma once
#include <zmq.hpp>
namespace Banking {
class IZMQSocket {
public:
    virtual ~IZMQSocket() = default;
    virtual bool send(zmq::message_t& msg, zmq::send_flags flags) = 0;
    virtual bool recv(zmq::message_t& msg, zmq::recv_flags flags) = 0;
};
} // namespace Banking
