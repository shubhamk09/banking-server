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

// Test fixture for ZMQRequest - ONLY using mocked components
class ZMQRequestTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Don't initialize any real ZMQ components
    }

    void TearDown() override {
        // Clean up
    }
};

TEST_F(ZMQRequestTest, RequestWithMockedRecv) {
    // Arrange
    Banking::Testing::MockZMQSocket mockSocket;
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

TEST_F(ZMQRequestTest, RequestWithMockedFailure) {
    Banking::Testing::MockZMQSocket mockSocket;
    
    // Mock a send failure
    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(false));
    // Mock recv to return false as well
    EXPECT_CALL(mockSocket, recv(_, _)).WillOnce(Return(false));
    
    Banking::ZMQRequest zmqRequest(&mockSocket);
    
    // This should handle the failure gracefully
    EXPECT_NO_THROW({
        std::string reply = zmqRequest.request("Test message");
        // Reply might be empty or contain error message
    });
}

// Simple tests that don't involve real ZMQ connections
TEST(ZMQBasicTest, MockSocketBasicTest) {
    Banking::Testing::MockZMQSocket mockSocket;
    
    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(true));
    EXPECT_CALL(mockSocket, recv(_, _)).WillOnce(Return(true));
    
    // Basic mock verification
    zmq::message_t msg("test", 4);
    EXPECT_TRUE(mockSocket.send(msg, zmq::send_flags::none));
    EXPECT_TRUE(mockSocket.recv(msg, zmq::recv_flags::none));
}
