/**
 * @file CustomerOperations.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Customer operations class for banking system database interactions
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DatabaseOperations.hpp"
#include "IOperations.hpp"
#include "Customer.hpp"

namespace Banking
{

/**
 * @brief Customer operations class for managing customer data
 * 
 * This class provides methods to perform CRUD operations on customers,
 * including customer information management and account relationships.
 * It implements the IOperations interface for message processing.
 */
class CustomerOperations : public IOperations
{
private:
    std::shared_ptr<IDatabaseOperations> dbOps;

public:
    /**
     * @brief Default constructor - creates CustomerOperations with default DatabaseOperations
     */
    CustomerOperations();

    /**
     * @brief Constructor with dependency injection
     * 
     * @param dbOperations Shared pointer to IDatabaseOperations implementation
     */
    explicit CustomerOperations(std::shared_ptr<IDatabaseOperations> dbOperations);

    /**
     * @brief Default destructor
     */
    ~CustomerOperations() = default;

    CustomerOperations(const CustomerOperations&) = delete;
    CustomerOperations& operator=(const CustomerOperations&) = delete;
    CustomerOperations(CustomerOperations&&) = default;
    CustomerOperations& operator=(CustomerOperations&&) = default;
public:
    /**
     * @brief Get customer name by customer ID
     * 
     * @param cstId The customer ID to query
     * @return std::string The customer's name
     */
    std::string getCustomerNameById(const std::string &cstId);

    /**
     * @brief Get customer password by customer ID
     * 
     * @param cstId The customer ID to query
     * @return std::string The customer's password
     */
    std::string getCustomerPasswordById(const std::string &cstId);

    /**
     * @brief Get customer account number by customer ID
     * 
     * @param cstId The customer ID to query
     * @return std::string The customer's account number
     */
    std::string getCustomerAccountById(const std::string &cstId);

    /**
     * @brief Get customer address by customer ID
     * 
     * @param cstId The customer ID to query
     * @return std::string The customer's address
     */
    std::string getCustomerAddressById(const std::string &cstId);

    /**
     * @brief Get customer branch by customer ID
     * 
     * @param cstId The customer ID to query
     * @return std::string The customer's branch
     */
    std::string getCustomerBranchById(const std::string &cstId);

    /**
     * @brief Set customer name by customer ID
     * 
     * @param cstId The customer ID to update
     * @param newName The new name to set
     */
    void setCustomerNameById(const std::string &cstId, const std::string& newName);

    /**
     * @brief Set customer password by customer ID
     * 
     * @param cstId The customer ID to update
     * @param newPassword The new password to set
     */
    void setCustomerPasswordById(const std::string &cstId, const std::string& newPassword);

    /**
     * @brief Set customer account number by customer ID
     * 
     * @param cstId The customer ID to update
     * @param newAccount The new account number to set
     */
    void setCustomerAccountById(const std::string &cstId, const std::string newAccount);

    /**
     * @brief Set customer address by customer ID
     * 
     * @param cstId The customer ID to update
     * @param newAddress The new address to set
     */
    void setCustomerAddressById(const std::string &cstId, const std::string& newAddress);

    /**
     * @brief Set customer branch by customer ID
     * 
     * @param cstId The customer ID to update
     * @param branchId The new branch ID to set
     */
    void setCustomerBranchById(const std::string &cstId, const std::string &branchId);

    /**
     * @brief Add a new customer to the database
     * 
     * @param cust Customer object to add (moved)
     */
    void addCustomer(Banking::Customer &&cust);

    /**
     * @brief Delete a customer from the database
     * 
     * @param cstId The customer ID to delete
     */
    void deleteCustomer(const std::string &cstId);

    /**
     * @brief Process incoming messages and perform the requested operation
     * 
     * @param message The JSON message containing operation details
     * @return nlohmann::json The result of the operation
     */
    nlohmann::json processMessage(const nlohmann::json& message) override;
    
};  

} // namespace Banking