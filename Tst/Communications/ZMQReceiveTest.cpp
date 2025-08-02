#include "ZMQReceive.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <zmq.hpp>
#include <thread>
#include "../Mocks/MockZMQSocket.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::DoAll;

// Test fixture for ZMQReceive
class ZMQReceiveTest : public ::testing::Test {
protected:
    Banking::ZMQContextManager* contextManagerPtr;

    void SetUp() override {
        contextManagerPtr = Banking::ZMQContextManager::getInstance();
    }

    void TearDown() override {
    }
};

// Add your ZMQReceive unit tests here, using MockZMQSocket for mocking

class MockReplierSocket : public Banking::IZMQSocket {
public:
    MOCK_METHOD(bool, send, (zmq::message_t& msg, zmq::send_flags flags), (override));
    MOCK_METHOD(bool, recv, (zmq::message_t& msg, zmq::recv_flags flags), (override));
};

TEST_F(ZMQReceiveTest, ReplySendsExpectedMessage) {
    MockReplierSocket mockSocket;
    std::string replyMessage = "ReplyMessage";
    zmq::message_t fakeReply(replyMessage.data(), replyMessage.size());

    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(true));

    Banking::ZMQReceive zmqReceive(&mockSocket);
    std::string result = zmqReceive.reply(replyMessage);
    EXPECT_EQ(result, replyMessage);
}

TEST_F(ZMQReceiveTest, ReceiveRequestReturnsExpectedMessage) {
    MockReplierSocket mockSocket;
    std::string requestMessage = "RequestMessage";
    zmq::message_t fakeRequest(requestMessage.data(), requestMessage.size());

    EXPECT_CALL(mockSocket, recv(_, _))
        .WillOnce(DoAll(
            [](zmq::message_t& msg, zmq::recv_flags) {
                msg = zmq::message_t("ReceivedRequest", 15);
                return true;
            },
            Return(true)
        ));

    Banking::ZMQReceive zmqReceive(&mockSocket);
    std::string result = zmqReceive.receiveRequest();
    EXPECT_EQ(result, "ReceivedRequest");
}