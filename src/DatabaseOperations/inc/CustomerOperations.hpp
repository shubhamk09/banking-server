/**
 * @file CustomerOperations.hpp
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

class CustomerOperations : public DatabaseOperations
{
public:
    CustomerOperations(connection_shptr &connPtr);
    ~CustomerOperations() = default;

    CustomerOperations(const CustomerOperations&) = default;
    CustomerOperations& operator=(const CustomerOperations&) = default;
    CustomerOperations(CustomerOperations&&) = default;
    CustomerOperations& operator=(CustomerOperations&&) = default;
public:
    std::string getCustomerNameById(std::string &empId);
    std::string getCustomerPasswordById(std::string &empId);
    std::string getCustomerAccountById(std::string &empId);
    std::string getCustomerAddressById(std::string &empId);
    std::string getCustomerBranchById(std::string &empId);
    
};  

} // namespace Banking