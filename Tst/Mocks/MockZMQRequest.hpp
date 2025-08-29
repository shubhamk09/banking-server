#ifndef MOCKZMQREQUEST_HPP
#define MOCKZMQREQUEST_HPP

#include <gmock/gmock.h>
#include <string>
#include "IZMQRequest.hpp"

namespace Banking {
namespace Testing {

class MockZMQRequest : public IZMQRequest {
public:
    MOCK_METHOD(std::string, request, (const std::string& requestMessage), (override));
};

} // namespace Testing
} // namespace Banking

#endif // MOCKZMQREQUEST_HPP
