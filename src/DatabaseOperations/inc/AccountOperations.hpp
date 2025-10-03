/**
 * @file AccountOperations.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Account operations class for banking system database interactions
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <sstream> // For std::ostringstream
#include <iomanip> // For std::hex, std::uppercase, std::setw, and std::setfill

#include "DatabaseOperations.hpp"
#include "IOperations.hpp"

namespace Banking
{

/**
 * @brief Account operations class for managing bank account data
 * 
 * This class provides methods to perform CRUD operations on bank accounts,
 * including balance management, transaction handling, and account status management.
 * It implements the IOperations interface for message processing.
 */
class AccountOperations : public IOperations
{
private:
    std::shared_ptr<IDatabaseOperations> dbOps;

public:
    /**
     * @brief Default constructor - creates AccountOperations with default DatabaseOperations
     */
    AccountOperations();

    /**
     * @brief Constructor with dependency injection
     * 
     * @param dbOperations Shared pointer to IDatabaseOperations implementation
     */
    explicit AccountOperations(std::shared_ptr<IDatabaseOperations> dbOperations);

    /**
     * @brief Default destructor
     */
    ~AccountOperations() = default;

    AccountOperations(const AccountOperations&) = delete;
    AccountOperations& operator=(const AccountOperations&) = delete;
    AccountOperations(AccountOperations&&) = default;
    AccountOperations& operator=(AccountOperations&&) = default;
public:
    /**
     * @brief Get the account balance by account ID
     * 
     * @param accNumber The account number to query
     * @return std::string The account balance as a string
     */
    std::string getAccountBalanceById(const std::string &accNumber);

    /**
     * @brief Get the account transactions by account ID
     * 
     * @param accNumber The account number to query
     * @return nlohmann::json JSON object containing account transactions
     */
    nlohmann::json getAccountTransactionsById(const std::string &accNumber);

    /**
     * @brief Get the account branch by account ID
     * 
     * @param accNumber The account number to query
     * @return std::string The branch name associated with the account
     */
    std::string getAccountBranchById(const std::string &accNumber);

    /**
     * @brief Check if an account is active
     * 
     * @param accNumber The account number to check
     * @return true If the account is active
     * @return false If the account is not active
     */
    bool isActiveAccount(const std::string &accNumber);

    /**
     * @brief Set the account balance by account ID
     * 
     * @param accNumber The account number to update
     * @param newBalance The new balance to set
     */
    void setAccountBalanceById(const std::string &accNumber, int newBalance);

    /**
     * @brief Set a new transaction for the account
     * 
     * @param accNumber The account number to update
     * @param newTransaction The new transaction data in JSON format
     */
    void setAccountTransactionById(const std::string &accNumber, nlohmann::json &newTransaction);

    /**
     * @brief Set the account status (active/inactive)
     * 
     * @param accNumber The account number to update
     * @param status The new status (true for active, false for inactive)
     */
    void setAccountStatusById(const std::string &accNumber, bool status);

    /**
     * @brief Set the account branch by account ID
     * 
     * @param accNumber The account number to update
     * @param newBranch The new branch name to set
     */
    void setAccountBranchById(const std::string &accNumber, const std::string &newBranch);

    /**
     * @brief Add a new account to the database
     * 
     * @param accNumber The account number
     * @param accBalance The initial account balance
     * @param accTransaction The initial transaction data
     * @param accBranch The branch associated with the account
     * @param isActive The account status (active/inactive)
     */
    void addAccount(const std::string &accNumber, const std::string &accBalance, nlohmann::json &accTransaction, 
                        const std::string &accBranch, bool &isActive);

    /**
     * @brief Delete an account from the database
     * 
     * @param accNumber The account number to delete
     */
    void deleteAccount(const std::string &accNumber);

    /**
     * @brief Convert JSON transaction data to hexadecimal string
     * 
     * @param accTransaction The transaction data in JSON format
     * @return std::string The hexadecimal representation of the JSON data
     */
    std::string createHexJson(nlohmann::json &accTransaction);

    /**
     * @brief Convert hexadecimal string back to JSON transaction data
     * 
     * @param hexJson The hexadecimal string to convert
     * @param accNumber The account number (used for logging)
     * @return nlohmann::json The parsed JSON transaction data
     */
    nlohmann::json createTransactionJson(std::string &hexJson, const std::string &accNumber);

    /**
     * @brief Process incoming messages and perform the requested operation
     * 
     * @param message The JSON message containing operation details
     * @return nlohmann::json The result of the operation
     */
    nlohmann::json processMessage(const nlohmann::json& message) override;
    
};  

} // namespace Banking