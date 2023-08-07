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
    std::string getAccountBalanceByNumber(std::string &accNumber);
    std::string getAccountTransactionsNumber(std::string &accNumber);
    std::string getAccountBranchByNumber(std::string &accNumber);
    bool isActiveAccount(std::string &accNumber);
    
};  

} // namespace Banking