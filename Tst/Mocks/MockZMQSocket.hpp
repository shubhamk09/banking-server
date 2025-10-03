#pragma once
#include <gmock/gmock.h>
#include "IZMQSocket.hpp"
#include <zmq.hpp>
namespace Banking {
namespace Testing {
class MockZMQSocket : public IZMQSocket {
public:
    MOCK_METHOD(bool, send, (zmq::message_t& msg, zmq::send_flags flags), (override));
    MOCK_METHOD(bool, recv, (zmq::message_t& msg, zmq::recv_flags flags), (override));
};
} // namespace Testing
} // namespace Banking
