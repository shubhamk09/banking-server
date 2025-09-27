#include "TcpServer.hpp"
#include <iostream>

namespace Communications {
namespace Socket {

TcpServer::TcpServer(asio::io_context& ioContext, uint16_t port)
    : ioContext_(ioContext)
    , serverSocket_(std::make_shared<TcpSocket>(ioContext))
    , running_(false)
    , messageHandler_(nullptr)
    , port_(port) {
}

TcpServer::~TcpServer() {
    stop();
}

void TcpServer::start(std::function<void(const std::string&, std::shared_ptr<ISocket>)> messageHandler) {
    messageHandler_ = messageHandler;
    
    try {
        serverSocket_->bind(port_);
        serverSocket_->listen();
        running_ = true;
        
        // Start accept thread
        acceptThread_ = std::thread(&TcpServer::handleConnections, this);
        
    } catch (const std::exception& e) {
        std::cerr << "Server failed to start: " << e.what() << std::endl;
        throw;
    }
}

void TcpServer::stop() {
    if (running_) {
        running_ = false;
        if (acceptThread_.joinable()) {
            acceptThread_.join();
        }
    }
}

void TcpServer::handleConnections() {
    while (running_) {
        try {
            auto clientSocket = serverSocket_->accept();
            
            // Start a new thread to handle this client's messages
            std::thread([this, clientSocket]() {
                try {
                    while (running_) {
                        auto message = clientSocket->receive();
                        if (!message.empty()) {
                            messageHandler_(message, clientSocket);
                        }
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Client connection error: " << e.what() << std::endl;
                }
            }).detach();
            
        } catch (const std::exception& e) {
            if (running_) {
                std::cerr << "Accept error: " << e.what() << std::endl;
            }
        }
    }
}

} // namespace Socket
} // namespace Communications
