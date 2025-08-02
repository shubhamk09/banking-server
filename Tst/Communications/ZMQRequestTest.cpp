#include "ZMQReceive.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <zmq.hpp>
#include "ZMQRequest.hpp"
#include <thread>
#include "../Mocks/MockZMQSocket.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::DoAll;


// Test fixture for ZMQRequest
class ZMQRequestTest : public ::testing::Test {
protected:
    Banking::ZMQContextManager* contextManagerPtr;
    zmq::socket_t* soocketPtr;

    void SetUp() override {
        contextManagerPtr = Banking::ZMQContextManager::getInstance();
    }

    void TearDown() override {
        if (soocketPtr) {
            soocketPtr->close();
            delete soocketPtr;
        }
    }
};

TEST_F(ZMQRequestTest, RequestWithMockedRecv) {
    // Arrange
    MockZMQSocket mockSocket;
    std::string expectedReply = "MockReply";
    zmq::message_t fakeReply(expectedReply.data(), expectedReply.size());

    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(true));
    EXPECT_CALL(mockSocket, recv(_, _))
        .WillOnce(DoAll(
            [](zmq::message_t& msg, zmq::recv_flags) {
                msg = zmq::message_t("MockReply", 9);
                return true;
            },
            Return(true)
        ));

    Banking::ZMQRequest zmqRequest(&mockSocket);
    std::string reply = zmqRequest.request("Hello, Server!");
    EXPECT_EQ(reply, expectedReply);
}
