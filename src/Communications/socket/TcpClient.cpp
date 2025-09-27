#include "TcpClient.hpp"
#include <iostream>

namespace Communications {
namespace Socket {

TcpClient::TcpClient(asio::io_context& ioContext)
    : ioContext_(ioContext)
    , running_(false) {
    clientSocket_ = std::make_shared<TcpSocket>(ioContext_);
}

TcpClient::~TcpClient() {
    disconnect();
}

void TcpClient::connect(const std::string& host, uint16_t port,
                       std::function<void(const std::string&)> messageHandler) {
    messageHandler_ = messageHandler;
    
    try {
        clientSocket_->connect(host, port);
        running_ = true;
        
        // Start receive thread
        receiveThread_ = std::thread(&TcpClient::handleMessages, this);
        
    } catch (const std::exception& e) {
        std::cerr << "Failed to connect: " << e.what() << std::endl;
        throw;
    }
}

void TcpClient::disconnect() {
    if (running_) {
        running_ = false;
        if (receiveThread_.joinable()) {
            receiveThread_.join();
        }
        clientSocket_->disconnect();
    }
}

bool TcpClient::sendMessage(const std::string& message) {
    try {
        if (isConnected()) {
            clientSocket_->send(message);
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to send message: " << e.what() << std::endl;
    }
    return false;
}

bool TcpClient::isConnected() const {
    return running_ && clientSocket_->isConnected();
}

void TcpClient::handleMessages() {
    while (running_) {
        try {
            auto message = clientSocket_->receive();
            if (!message.empty()) {
                messageHandler_(message);
            }
        } catch (const std::exception& e) {
            if (running_) {
                std::cerr << "Receive error: " << e.what() << std::endl;
                break;
            }
        }
    }
    running_ = false;
}

} // namespace Socket
} // namespace Communications
