#include "TcpServer.hpp"
#include <iostream>
#include <asio.hpp>

using namespace Communications::Socket;

void handleClientMessage(const std::string& message, std::shared_ptr<ISocket> client) {
    std::cout << "Received message: " << message << std::endl;
    // Echo back to client
    client->send("Server received: " + message);
}

int main() {
    try {
        asio::io_context ioContext;
        TcpServer server(ioContext, 8080);
        
        std::cout << "Starting server on port 8080..." << std::endl;
        server.start(handleClientMessage);
        
        // Run the IO context
        ioContext.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
