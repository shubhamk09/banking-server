/**
 * @file IOperations.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief IOperations implementation for banking system
 * @version 0.1
 * @date 2025-08-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
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