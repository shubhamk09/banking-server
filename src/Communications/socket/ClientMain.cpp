#include "TcpClient.hpp"
#include <iostream>
#include <asio.hpp>

using namespace Communications::Socket;

void handleServerMessage(const std::string& message) {
    std::cout << "Received from server: " << message << std::endl;
}

int main() {
    try {
        asio::io_context ioContext;
        TcpClient client(ioContext);
        
        std::cout << "Connecting to server..." << std::endl;
        client.connect("localhost", 8080, handleServerMessage);
        
        // Start a thread to run the IO context
        std::thread ioThread([&ioContext]() {
            ioContext.run();
        });
        
        // Main loop for sending messages
        std::string message;
        while (client.isConnected()) {
            std::getline(std::cin, message);
            if (message == "quit") {
                break;
            }
            if (!client.sendMessage(message)) {
                std::cout << "Failed to send message" << std::endl;
                break;
            }
        }
        
        client.disconnect();
        ioContext.stop();
        ioThread.join();
        
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
