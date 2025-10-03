#include "ZMQReceive.hpp"
#include "ZMQContextManager.hpp"
#include "Logger.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <zmq.hpp>
#include "ZMQRequest.hpp"
#include <thread>
#include "../Mocks/MockZMQSocket.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::DoAll;

// ================= ZMQContextManager Tests =================
TEST(ZMQContextManagerTest, SingletonPattern) {
    Banking::ZMQContextManager* instance1 = Banking::ZMQContextManager::getInstance();
    Banking::ZMQContextManager* instance2 = Banking::ZMQContextManager::getInstance();
    
    EXPECT_EQ(instance1, instance2);
    EXPECT_NE(instance1, nullptr);
}

TEST(ZMQContextManagerTest, GetContext) {
    Banking::ZMQContextManager* manager = Banking::ZMQContextManager::getInstance();
    
    // Context should be valid (we can't directly test much without making actual connections)
    // But we can verify it doesn't crash
    EXPECT_NO_THROW({
        zmq::context_t& ctx = manager->getContext();
        (void)ctx; // Suppress unused variable warning
    });
}

// ================= ZMQRequest Real Implementation Tests =================
class ZMQRequestRealTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize logger for real tests
        Banking::Logger::Init();
    }
};

TEST_F(ZMQRequestRealTest, ConstructorWithSocket) {
    Banking::Testing::MockZMQSocket mockSocket;
    
    // Test constructor that takes a socket
    EXPECT_NO_THROW({
        Banking::ZMQRequest request(&mockSocket);
    });
}

TEST_F(ZMQRequestRealTest, RequestWithMockSocket) {
    Banking::Testing::MockZMQSocket mockSocket;
    std::string expectedReply = "TestReply";
    
    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(true));
    EXPECT_CALL(mockSocket, recv(_, _))
        .WillOnce(DoAll(
            [expectedReply](zmq::message_t& msg, zmq::recv_flags) {
                msg = zmq::message_t(expectedReply.data(), expectedReply.size());
                return true;
            },
            Return(true)
        ));
    
    Banking::ZMQRequest request(&mockSocket);
    std::string result = request.request("TestMessage");
    EXPECT_EQ(result, expectedReply);
}

// ================= ZMQReceive Real Implementation Tests =================
class ZMQReceiveRealTest : public ::testing::Test {
protected:
    void SetUp() override {
        Banking::Logger::Init();
    }
};

TEST_F(ZMQReceiveRealTest, ConstructorWithSocket) {
    Banking::Testing::MockZMQSocket mockSocket;
    
    EXPECT_NO_THROW({
        Banking::ZMQReceive receiver(&mockSocket);
    });
}

TEST_F(ZMQReceiveRealTest, ReplyWithMockSocket) {
    Banking::Testing::MockZMQSocket mockSocket;
    std::string testMessage = "ReplyMessage";
    
    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(true));
    
    Banking::ZMQReceive receiver(&mockSocket);
    std::string result = receiver.reply(testMessage);
    EXPECT_EQ(result, testMessage);
}

TEST_F(ZMQReceiveRealTest, ReceiveRequestWithMockSocket) {
    Banking::Testing::MockZMQSocket mockSocket;
    std::string expectedMessage = "ReceivedMessage";
    
    EXPECT_CALL(mockSocket, recv(_, _))
        .WillOnce(DoAll(
            [expectedMessage](zmq::message_t& msg, zmq::recv_flags) {
                msg = zmq::message_t(expectedMessage.data(), expectedMessage.size());
                return true;
            },
            Return(true)
        ));
    
    Banking::ZMQReceive receiver(&mockSocket);
    std::string result = receiver.receiveRequest();
    EXPECT_EQ(result, expectedMessage);
}

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
