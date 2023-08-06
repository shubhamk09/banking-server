/**
 * @file Customer.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BANKING_CUSTOMER_HPP
#define BANKING_CUSTOMER_HPP
#include "User.hpp"
namespace Banking{
    class Customer: public User
    {
    private:
        std::string accountNumber;

    public:
        Customer(std::string &id, std::string &name, std::string &password, std::string &branch, std::string &address, std::string &accountNumber);
        ~Customer() = default;
        
        Customer(const Customer&) = default;
        Customer& operator=(const Customer&) = default;
        Customer(Customer&&) = default;
        Customer& operator=(Customer&&) = default;


        std::string getAccountNumber();
        void setAccountNumber(std::string accounNumber);
    };
}
#endif //BANKING_CUSTOMER_HPP

