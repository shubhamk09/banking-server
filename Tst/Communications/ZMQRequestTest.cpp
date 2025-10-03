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

using MockZMQSocket = Banking::Testing::MockZMQSocket;

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

// ================= Additional Real Implementation Tests =================

TEST_F(ZMQRequestTest, ConstructorWithMockSocketDoesNotCrash) {
    MockZMQSocket mockSocket;
    
    EXPECT_NO_THROW({
        Banking::ZMQRequest request(&mockSocket);
    });
}

TEST_F(ZMQRequestTest, DestructorHandlesSocketCorrectly) {
    MockZMQSocket* mockSocket = new MockZMQSocket();
    
    EXPECT_NO_THROW({
        Banking::ZMQRequest request(mockSocket);
        // Destructor should not delete the socket since ownsSocket is false
    });
    
    delete mockSocket; // Clean up manually
}

TEST_F(ZMQRequestTest, RequestMethodWithVariousMessages) {
    MockZMQSocket mockSocket;
    
    // Test with empty message
    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(true));
    EXPECT_CALL(mockSocket, recv(_, _))
        .WillOnce(DoAll(
            [](zmq::message_t& msg, zmq::recv_flags) {
                msg = zmq::message_t("", 0);
                return true;
            },
            Return(true)
        ));
    
    Banking::ZMQRequest request(&mockSocket);
    std::string result1 = request.request("");
    EXPECT_EQ(result1, "");
    
    // Test with special characters
    std::string specialMsg = "Special: !@#$%";
    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(true));
    EXPECT_CALL(mockSocket, recv(_, _))
        .WillOnce(DoAll(
            [specialMsg](zmq::message_t& msg, zmq::recv_flags) {
                msg = zmq::message_t(specialMsg.data(), specialMsg.size());
                return true;
            },
            Return(true)
        ));
    
    std::string result2 = request.request("Send special");
    EXPECT_EQ(result2, specialMsg);
}

TEST_F(ZMQRequestTest, RequestMethodErrorHandling) {
    MockZMQSocket mockSocket;
    
    // Test send failure
    EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(false));
    EXPECT_CALL(mockSocket, recv(_, _)).WillOnce(Return(false));
    
    Banking::ZMQRequest request(&mockSocket);
    
    // Should handle failures gracefully
    EXPECT_NO_THROW({
        std::string result = request.request("Test message");
        // Result may be empty or contain error info
    });
}
