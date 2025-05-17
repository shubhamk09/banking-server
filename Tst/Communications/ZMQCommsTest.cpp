#include "ZMQReceive.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <zmq.hpp>
#include "ZMQRequest.hpp"
#include <thread>


// Test fixture for ZMQReceive
class ZMQCommsTest : public ::testing::Test {
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

TEST_F(ZMQCommsTest, TestReceiveReplyRequest) {
    // // Arrange
    // std::string bindAddress = "tcp://127.0.0.1:5555";
    // std::string expectedMessage = "Test Message";

    // zmq::message_t mockMessage(expectedMessage.data(), expectedMessage.size());
    // Banking::ZMQReceive zmqReceive(bindAddress);
    // std::string response;

    // // Act
    // std::thread requestorThread([&bindAddress, &response]() {
    //     Banking::ZMQRequest requestor(bindAddress);
    //     std::string requestMessage = "Test Message";
    //     response = requestor.request(requestMessage);
    // });

    // std::string receivedMessage = zmqReceive.receiveRequest();
    // ASSERT_EQ(receivedMessage, expectedMessage);
    // std::string replyMessage = "Reply Message";
    // zmqReceive.reply(receivedMessage);
    // requestorThread.join();
    // // Assert
    // ASSERT_EQ(response, expectedMessage);
}