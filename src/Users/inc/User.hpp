/**
 * @file User.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
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
class User
{
private:
    std::string id;
    std::string name;
    std::string password;
    std::string branch;
    std::string address;

public:
    User(const std::string &id, const std::string &name, const std::string &password, const std::string &branch, const std::string &address);
    virtual ~User() = default;

    User(const User&) = default;
    User& operator=(const User&) = default;
    User(User&&) = default;
    User& operator=(User&&) = default;

public:
    virtual std::string getId();
    virtual void setId(const std::string &id);
    virtual std::string getName();
    virtual void setName(const std::string &name);
    virtual std::string getPassword();
    virtual void setPassword(const std::string &password);
    virtual std::string getBranch();
    virtual void setBranch(const std::string &branch);
    virtual std::string getAddress();
    virtual void setAddress(const std::string &address);

    static std::shared_ptr<User> createUser(const std::string &id, const std::string &name, const std::string &password, const std::string &address, const std::string &branch, const std::string &designationOrAccountNumber);
};
}
#endif //BANKING_USER_HPP