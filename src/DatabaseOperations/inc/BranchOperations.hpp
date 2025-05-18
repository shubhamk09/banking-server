/**
 * @file BranchOperations.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DatabaseOperations.hpp"
#include "IOperations.hpp"

namespace Banking
{

class BranchOperations : public IOperations
{
public:
    BranchOperations();
    ~BranchOperations() = default;

    BranchOperations(const BranchOperations&) = default;
    BranchOperations& operator=(const BranchOperations&) = default;
    BranchOperations(BranchOperations&&) = default;
    BranchOperations& operator=(BranchOperations&&) = default;
public:
    std::string getBranchNameById(const std::string &branchId);
    std::string getBranchCityById(const std::string &branchId);
    std::string getBranchAddressById(const std::string &branchId);
    std::string getBranchManagerById(const std::string &branchId);
    bool isActiveBranch(const std::string &branchId);
    void setBranchNameById(const std::string &branchId, const std::string &newName);
    void setBranchCityById(const std::string &branchId, const std::string &newCity);
    void setBranchAddressById(const std::string &branchId, const std::string &newAdd);
    void setBranchManagerById(const std::string &branchId, const std::string &newBranchManagerId);
    void addBranch(const std::string &branchId, const std::string &newName, const std::string &newCity, const std::string &newAdd, const std::string &newBranchManagerId);
    void deleteBranch(const std::string &branchId);
    nlohmann::json processMessage(const nlohmann::json& message) override;
    
};  

} // namespace Banking