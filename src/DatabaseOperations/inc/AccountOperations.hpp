/**
 * @file AccountOperations.hpp
 * @author your name (you@domain.com)
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
    std::string getAccountBalanceById(std::string &accNumber);
    nlohmann::json getAccountTransactionsById(std::string &accNumber);
    std::string getAccountBranchById(std::string &accNumber);
    bool isActiveAccount(std::string &accNumber);
    void setAccountBalanceById(std::string &accNumber, int newBalance);
    void setAccountTransactionById(std::string &accNumber, nlohmann::json &newTransaction);
    void setAccountStatusById(std::string &accNumber, bool status);
    void setAccountBranchById(std::string &accNumber, std::string &newBranch);
    void addAccount(std::string &accNumber, std::string &accBalance, nlohmann::json &accTransaction, 
                        std::string &accBranch, bool &isActive);
    void deleteAccount(std::string &accNumber);
    std::string createHexJson(nlohmann::json &accTransaction);
    nlohmann::json createTransactionJson(std::string &hexJson, std::string &accNumber);
    
};  

} // namespace Banking