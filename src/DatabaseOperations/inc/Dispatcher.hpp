#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <nlohmann/json.hpp> // Include the JSON library
#include "IOperations.hpp"

namespace Banking {

class Dispatcher {
private:
    std::unordered_map<std::string, std::shared_ptr<IOperations>> operationsMap;

    // Private constructor for Singleton
    Dispatcher();

public:
    // Delete copy constructor and assignment operator
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

    // Get the Singleton instance
    static Dispatcher& getInstance();

    void registerOperation(const std::string& key, std::shared_ptr<IOperations> operation);

    std::string dispatch(const std::string& key, const nlohmann::json& message);
};

} // namespace Banking
