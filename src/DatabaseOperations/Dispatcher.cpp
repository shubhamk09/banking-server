/**
 * @file Dispatcher.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Implementation of Message dispatcher for routing operations in banking system
 * @version 0.1
 * @date 2025-08-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Dispatcher.hpp"

namespace Banking {

// Private constructor for Singleton
Dispatcher::Dispatcher() = default;

// Get the Singleton instance
Dispatcher& Dispatcher::getInstance() {
    static Dispatcher instance;
    return instance;
}

// Register an operation
void Dispatcher::registerOperation(const std::string& key, std::shared_ptr<IOperations> operation) {
    operationsMap[key] = operation;
}

// Dispatch a message to the appropriate operation
std::string Dispatcher::dispatch(const std::string& key, const nlohmann::json& message) {
    if (operationsMap.find(key) != operationsMap.end()) {
        return operationsMap[key]->processMessage(message).dump();
    }
    return "Operation not found";
}

} // namespace Banking