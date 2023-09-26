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
    std::string getCustomerNameById(const std::string &cstId);
    std::string getCustomerPasswordById(const std::string &cstId);
    std::string getCustomerAccountById(const std::string &cstId);
    std::string getCustomerAddressById(const std::string &cstId);
    std::string getCustomerBranchById(const std::string &cstId);
    void setCustomerNameById(const std::string &cstId, const std::string& newName);
    void setCustomerPasswordById(const std::string &cstId, const std::string& newPassword);
    void setCustomerAccountById(const std::string &cstId, const std::string newAccount);
    void setCustomerAddressById(const std::string &cstId, const std::string& newAddress);
    void setCustomerBranchById(const std::string &cstId, const std::string &branchId);
    void addCustomer(Banking::Customer &&cust);
    void deleteCustomer(const std::string &cstId);
    
};  

} // namespace Banking