#include "Connection.hpp"
#include "ZMQReceive.hpp"

int main() {
    using namespace Banking;

    std::shared_ptr<Connection> connPtr = std::make_shared<Connection>();
    // Get the singleton instance of ZMQReceive, listening on a specific address
    auto& zmqReceiver = ZMQReceive::getInstance("tcp://*:5501");

    std::cout << "Server is listening for incoming requests..." << std::endl;

    // Event loop to listen for incoming requests
    while (true) {
        // Receive a request from the client
        std::string request = zmqReceiver.receiveRequest();

        // Here you can process the request and generate a response
        std::string response = connPtr->executeQuery(request);

        // Send the reply back to the client
        zmqReceiver.reply(response);
    }
    return 0;
}