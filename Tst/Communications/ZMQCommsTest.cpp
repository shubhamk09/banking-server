#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "ZMQComms.hpp"

namespace Banking {

class ZMQCommsTest : public ::testing::Test {
protected:
    ZMQComms* zmqComms;

    void SetUp() override {
        zmqComms = ZMQComms::getInstance(); // Get the singleton instance
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Allow time for sockets to connect
    }

    void TearDown() override {
        // Cleanup if necessary
    }
};

// Test for sendMessage and receiveMessage
TEST_F(ZMQCommsTest, SendMessageAndReceiveMessage) {
    // Arrange
    const std::string topic = "TestTopic";
    const std::string message = "Hello, ZMQ!";

    // Act
    zmqComms->sendMessage(topic, message); // Send the message
    std::string receivedMessage = zmqComms->receiveMessage(); // Receive the message

    // Assert
    EXPECT_EQ(receivedMessage, message); // Verify the received message matches the sent message
}

} // namespace Banking