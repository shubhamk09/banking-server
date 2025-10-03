#include "MockZMQSocket.hpp"

using ::testing::Return;
using ::testing::_;

// Example usage in a test
// TEST_F(ZMQCommsTest, RequestWithMockedRecv) {
//     MockZMQSocket mockSocket;
//     zmq::message_t fakeReply("MockReply", 9);
//     EXPECT_CALL(mockSocket, recv(_, _))
//         .WillOnce(DoAll(
//             [](zmq::message_t& msg, zmq::recv_flags) {
//                 msg = zmq::message_t("MockReply", 9);
//                 return true;
//             },
//             Return(true)
//         ));
//     // You can also mock send if needed
//     EXPECT_CALL(mockSocket, send(_, _)).WillOnce(Return(true));
//     // Now use mockSocket in your ZMQRequest logic
// }
