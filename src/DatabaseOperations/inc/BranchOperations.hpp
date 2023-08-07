/**
 * @file BranchOperations.hpp
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

class BranchOperations : public DatabaseOperations
{
public:
    BranchOperations(connection_shptr &connPtr);
    ~BranchOperations() = default;

    BranchOperations(const BranchOperations&) = default;
    BranchOperations& operator=(const BranchOperations&) = default;
    BranchOperations(BranchOperations&&) = default;
    BranchOperations& operator=(BranchOperations&&) = default;
public:
    std::string getBranchNameById(std::string &empId);
    std::string getBranchCityById(std::string &empId);
    std::string getBranchAddressById(std::string &empId);
    std::string getBranchManagerById(std::string &empId);
    bool isActiveBranch(std::string &empId);
    
};  

} // namespace Banking