/**
 * @file AccountOperations.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <sstream> // For std::ostringstream
#include <iomanip> // For std::hex, std::uppercase, std::setw, and std::setfill

#include "DatabaseOperations.hpp"

namespace Banking
{

class AccountOperations : public DatabaseOperations
{
public:
    AccountOperations(connection_shptr &connPtr);
    ~AccountOperations() = default;

    AccountOperations(const AccountOperations&) = default;
    AccountOperations& operator=(const AccountOperations&) = default;
    AccountOperations(AccountOperations&&) = default;
    AccountOperations& operator=(AccountOperations&&) = default;
public:
    std::string getAccountBalanceById(const std::string &accNumber);
    nlohmann::json getAccountTransactionsById(const std::string &accNumber);
    std::string getAccountBranchById(const std::string &accNumber);
    bool isActiveAccount(const std::string &accNumber);
    void setAccountBalanceById(const std::string &accNumber, int newBalance);
    void setAccountTransactionById(const std::string &accNumber, nlohmann::json &newTransaction);
    void setAccountStatusById(const std::string &accNumber, bool status);
    void setAccountBranchById(const std::string &accNumber, const std::string &newBranch);
    void addAccount(const std::string &accNumber, const std::string &accBalance, nlohmann::json &accTransaction, 
                        const std::string &accBranch, bool &isActive);
    void deleteAccount(const std::string &accNumber);
    std::string createHexJson(nlohmann::json &accTransaction);
    nlohmann::json createTransactionJson(std::string &hexJson, const std::string &accNumber);
    
};  

} // namespace Banking