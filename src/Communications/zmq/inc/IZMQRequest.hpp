#ifndef IZMQREQUEST_HPP
#define IZMQREQUEST_HPP

#include <string>

namespace Banking {

/**
 * @brief Interface for ZMQ Request operations
 */
class IZMQRequest {
public:
    virtual ~IZMQRequest() = default;
    
    /**
     * @brief Send a request and receive a reply
     * @param requestMessage The message to send
     * @return The reply received
     */
    virtual std::string request(const std::string& requestMessage) = 0;
};

} // namespace Banking

#endif // IZMQREQUEST_HPP
