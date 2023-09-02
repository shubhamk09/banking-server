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
#include "Customer.hpp"

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
    std::string getCustomerNameById(std::string &cstId);
    std::string getCustomerPasswordById(std::string &cstId);
    std::string getCustomerAccountById(std::string &cstId);
    std::string getCustomerAddressById(std::string &cstId);
    std::string getCustomerBranchById(std::string &cstId);
    void setCustomerNameById(std::string &cstId, std::string& newName);
    void setCustomerPasswordById(std::string &cstId, std::string& newPassword);
    void setCustomerAccountById(std::string &cstId, std::string newAccount);
    void setCustomerAddressById(std::string &cstId, std::string& newAddress);
    void setCustomerBranchById(std::string &cstId, std::string &branchId);
    void addCustomer(Banking::Customer &&cust);
    void deleteCustomer(std::string &cstId);
    
};  

} // namespace Banking