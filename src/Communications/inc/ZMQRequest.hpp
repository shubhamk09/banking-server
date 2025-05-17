#ifndef ZMQREQUEST_HPP
#define ZMQREQUEST_HPP

#include "ZMQContextManager.hpp"

namespace Banking {

    class ZMQRequest {
    private:
        zmq::socket_t requestorSocket;
    
        // Private constructor for Singleton
        ZMQRequest(const std::string &bindAddress);

    public:
        // Delete copy constructor and assignment operator
        ZMQRequest(const ZMQRequest&) = delete;
        ZMQRequest& operator=(const ZMQRequest&) = delete;
    
        // Get the Singleton instance
        static ZMQRequest& getInstance(const std::string &bindAddress);
    
        // Send a request and receive a reply
        std::string request(const std::string &requestMessage);
    };
    
    } // namespace Banking
using requestor_shptr = std::shared_ptr<Banking::ZMQRequest>;
#endif //ZMQRequest_HPP