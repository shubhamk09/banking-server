#include "Dispatcher.hpp"
#include "DatabaseOperations.hpp"
#include "CustomerOperations.hpp"
#include "EmployeeOperations.hpp"
#include "AccountOperations.hpp"
#include "BranchOperations.hpp"

int main() {
    using namespace Banking;

    // Create shared DatabaseOperations instance
    auto dbOps = std::make_shared<DatabaseOperations>();

    // Create specific operations
    auto customerOps = std::make_shared<CustomerOperations>();
    auto employeeOps = std::make_shared<EmployeeOperations>();
    auto accountOps = std::make_shared<AccountOperations>();
    auto branchOps = std::make_shared<BranchOperations>();

    // Create and configure the dispatcher
    Dispatcher &dispatcher = Dispatcher::getInstance();
    dispatcher.registerOperation("Customer", customerOps);
    dispatcher.registerOperation("Employee", employeeOps);
    dispatcher.registerOperation("Account", accountOps);
    dispatcher.registerOperation("Branch", branchOps);
    // Example message
    nlohmann::json message;
    message["Operation"] = "Account";
    message["OperationType"] = "get";
    message["ColumnName"] = "Account_balance";
    message["Data"] = nlohmann::json::array({"1234567890"});

    // Dispatch messages
    std::string response = dispatcher.dispatch(message["Operation"], message);
    std::cout << "Response: " << response << std::endl;

    return 0;
}