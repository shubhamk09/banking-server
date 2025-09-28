/**
 * @file TcpSocket.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Implementation of TCP Socket class
 * @version 0.1
 * @date 2023-08-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TcpSocket.hpp"
#include "Logger.hpp"
#include <stdexcept>

namespace Communications {
namespace Socket {

TcpSocket::TcpSocket(asio::io_context& ioContext)
    : ioContext_(ioContext)
    , socket_(ioContext)
    , acceptor_(ioContext)
    , isServer_(false)
    , connected_(false) {
}

TcpSocket::TcpSocket(asio::io_context& ioContext, asio::ip::tcp::socket socket)
    : ioContext_(ioContext)
    , socket_(std::move(socket))
    , acceptor_(ioContext)
    , isServer_(false)
    , connected_(true) {
}

TcpSocket::~TcpSocket() {
    if (isConnected()) {
        disconnect();
    }
}

void TcpSocket::connect(const std::string& host, uint16_t port) {
    if (isServer_) {
        BANKING_LOGGER_ERROR("Cannot connect a server socket");
        throw std::runtime_error("Cannot connect a server socket");
    }

    BANKING_LOGGER_INFO("Resolving host {}:{}", host, port);
    asio::ip::tcp::resolver resolver(ioContext_);
    auto endpoints = resolver.resolve(host, std::to_string(port));

    asio::error_code ec;
    asio::connect(socket_, endpoints, ec);

    if (ec) {
        BANKING_LOGGER_ERROR("Connection failed: {}", ec.message());
        throw std::runtime_error("Failed to connect: " + ec.message());
    }

    connected_ = true;
    BANKING_LOGGER_INFO("Connected to {}:{}", host, port);
}

void TcpSocket::disconnect() {
    if (socket_.is_open()) {
        asio::error_code ec;
        socket_.close(ec);
        if (ec) {
            BANKING_LOGGER_ERROR("Error during socket close: {}", ec.message());
        } else {
            BANKING_LOGGER_INFO("Socket closed successfully");
        }
    }
    connected_ = false;
}

bool TcpSocket::isConnected() const {
    return connected_ && socket_.is_open();
}

size_t TcpSocket::send(const std::string& message) {
    if (!isConnected()) {
        throw std::runtime_error("Socket is not connected");
    }

    asio::error_code ec;
    size_t written = asio::write(socket_, asio::buffer(message), ec);

    if (ec) {
        throw std::runtime_error("Failed to send data: " + ec.message());
    }

    return written;
}

std::string TcpSocket::receive(size_t maxLength) {
    if (!isConnected()) {
        throw std::runtime_error("Socket is not connected");
    }

    std::vector<char> buffer(maxLength);
    asio::error_code ec;
    
    size_t length = socket_.read_some(asio::buffer(buffer), ec);

    if (ec) {
        // Check if this is a normal client disconnect (EOF)
        if (ec == asio::error::eof) {
            BANKING_LOGGER_INFO("Client disconnected normally (EOF)");
            throw std::runtime_error("Client disconnected");
        }
        // For other errors, throw with the original message
        throw std::runtime_error("Failed to receive data: " + ec.message());
    }

    return std::string(buffer.begin(), buffer.begin() + length);
}

void TcpSocket::bind(uint16_t port) {
    if (connected_) {
        throw std::runtime_error("Socket is already connected");
    }

    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
    acceptor_.open(endpoint.protocol());
    
    // Set socket options
    acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.set_option(asio::socket_base::linger(true, 0));
    
    acceptor_.bind(endpoint);
    
    isServer_ = true;
}

void TcpSocket::listen(int backlog) {
    if (!isServer_) {
        throw std::runtime_error("Not a server socket");
    }

    acceptor_.listen(backlog);
}

std::shared_ptr<ISocket> TcpSocket::accept() {
    if (!isServer_) {
        throw std::runtime_error("Not a server socket");
    }

    asio::ip::tcp::socket clientSocket(ioContext_);
    acceptor_.accept(clientSocket);

    return std::make_shared<TcpSocket>(ioContext_, std::move(clientSocket));
}

} // namespace Socket
} // namespace Communications
