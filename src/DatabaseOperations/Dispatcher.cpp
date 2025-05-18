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