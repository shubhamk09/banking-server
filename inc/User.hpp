/**
 * @file User.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
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
    User(std::string &id, std::string &name, std::string &password, std::string &branch, std::string &address);
    virtual ~User() = default;

    User(const User&) = default;
    User& operator=(const User&) = default;
    User(User&&) = default;
    User& operator=(User&&) = default;

public:
    virtual std::string getId();
    virtual void set(int &id);
    virtual std::string getName();
    virtual void setName(std::string &name);
    virtual std::string getPassword();
    virtual void setPassword(std::string &password);
    virtual std::string getBranch();
    virtual void setBranch(std::string &branch);
    virtual std::string getAddress();
    virtual void setAddress(std::string &address);
};
}
