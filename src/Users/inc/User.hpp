/**
 * @file User.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Base user class for banking system user management
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BANKING_USER_HPP
#define BANKING_USER_HPP

#include <iostream>
#include <memory>
#include <regex>


// Forward declaration of the Customer class
// namespace Banking {
//     class Customer;
// }

// Forward declaration of the Customer class
// namespace Banking {
//     class Employee;
// }

namespace Banking{

/**
 * @brief Base class for all users in the banking system
 * 
 * This abstract class provides common functionality for both
 * customers and employees, including basic user information
 * management and user creation factory method.
 */
class User
{
private:
    std::string id;       ///< User unique identifier
    std::string name;     ///< User full name
    std::string password; ///< User password (should be hashed in production)
    std::string branch;   ///< Associated branch
    std::string address;  ///< User address

public:
    /**
     * @brief Construct a new User object
     * 
     * @param id Unique user identifier
     * @param name User's full name
     * @param password User's password
     * @param branch Associated branch
     * @param address User's address
     */
    User(const std::string &id, const std::string &name, const std::string &password, const std::string &branch, const std::string &address);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~User() = default;

    // Copy and move constructors/operators
    User(const User&) = default;
    User& operator=(const User&) = default;
    User(User&&) = default;
    User& operator=(User&&) = default;

public:
    /**
     * @brief Get the user ID
     * 
     * @return std::string The user ID
     */
    virtual std::string getId();
    
    /**
     * @brief Set the user ID
     * 
     * @param id The new user ID
     */
    virtual void setId(const std::string &id);
    
    /**
     * @brief Get the user name
     * 
     * @return std::string The user name
     */
    virtual std::string getName();
    
    /**
     * @brief Set the user name
     * 
     * @param name The new user name
     */
    virtual void setName(const std::string &name);
    
    /**
     * @brief Get the user password
     * 
     * @return std::string The user password
     */
    virtual std::string getPassword();
    
    /**
     * @brief Set the user password
     * 
     * @param password The new password
     */
    virtual void setPassword(const std::string &password);
    
    /**
     * @brief Get the user's branch
     * 
     * @return std::string The branch name
     */
    virtual std::string getBranch();
    
    /**
     * @brief Set the user's branch
     * 
     * @param branch The new branch name
     */
    virtual void setBranch(const std::string &branch);
    
    /**
     * @brief Get the user's address
     * 
     * @return std::string The user address
     */
    virtual std::string getAddress();
    
    /**
     * @brief Set the user's address
     * 
     * @param address The new address
     */
    virtual void setAddress(const std::string &address);

    /**
     * @brief Factory method to create user objects
     * 
     * Creates either Customer or Employee objects based on the parameters.
     * This method determines the user type and returns the appropriate object.
     * 
     * @param id Unique user identifier
     * @param name User's full name
     * @param password User's password
     * @param address User's address
     * @param branch Associated branch
     * @param designationOrAccountNumber Employee designation or customer account number
     * @return std::shared_ptr<User> Shared pointer to the created user object
     */
    static std::shared_ptr<User> createUser(const std::string &id, const std::string &name, const std::string &password, const std::string &address, const std::string &branch, const std::string &designationOrAccountNumber);
};
}
#endif //BANKING_USER_HPP