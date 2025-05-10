#pragma once

#include <nlohmann/json.hpp> // Include the JSON library

namespace Banking {

class IOperations {
public:
    virtual ~IOperations() = default;

    // Define a common interface for all operations
    virtual nlohmann::json processMessage(const nlohmann::json& message) = 0;
};

} // namespace Banking