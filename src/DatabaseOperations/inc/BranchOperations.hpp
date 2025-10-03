/**
 * @file BranchOperations.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Branch operations class for banking system database interactions
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

/**
 * @brief Branch operations class for managing bank branch data
 * 
 * This class provides methods to perform CRUD operations on bank branches,
 * including branch information management and status tracking.
 * It implements the IOperations interface for message processing.
 */
class BranchOperations : public IOperations
{
private:
    std::shared_ptr<IDatabaseOperations> dbOps;

public:
    /**
     * @brief Default constructor - creates BranchOperations with default DatabaseOperations
     */
    BranchOperations();

    /**
     * @brief Constructor with dependency injection
     * 
     * @param dbOperations Shared pointer to IDatabaseOperations implementation
     */
    explicit BranchOperations(std::shared_ptr<IDatabaseOperations> dbOperations);

    /**
     * @brief Default destructor
     */
    ~BranchOperations() = default;

    BranchOperations(const BranchOperations&) = delete;
    BranchOperations& operator=(const BranchOperations&) = delete;
    BranchOperations(BranchOperations&&) = default;
    BranchOperations& operator=(BranchOperations&&) = default;
public:
    /**
     * @brief Get the branch name by branch ID
     * 
     * @param branchId The branch ID to query
     * @return std::string The branch name
     */
    std::string getBranchNameById(const std::string &branchId);

    /**
     * @brief Get the branch city by branch ID
     * 
     * @param branchId The branch ID to query
     * @return std::string The city where the branch is located
     */
    std::string getBranchCityById(const std::string &branchId);

    /**
     * @brief Get the branch address by branch ID
     * 
     * @param branchId The branch ID to query
     * @return std::string The full address of the branch
     */
    std::string getBranchAddressById(const std::string &branchId);

    /**
     * @brief Get the branch manager ID by branch ID
     * 
     * @param branchId The branch ID to query
     * @return std::string The manager ID associated with the branch
     */
    std::string getBranchManagerById(const std::string &branchId);

    /**
     * @brief Check if a branch is active
     * 
     * @param branchId The branch ID to check
     * @return true If the branch is active
     * @return false If the branch is not active
     */
    bool isActiveBranch(const std::string &branchId);

    /**
     * @brief Set the branch name by branch ID
     * 
     * @param branchId The branch ID to update
     * @param newName The new branch name to set
     */
    void setBranchNameById(const std::string &branchId, const std::string &newName);

    /**
     * @brief Set the branch city by branch ID
     * 
     * @param branchId The branch ID to update
     * @param newCity The new city to set
     */
    void setBranchCityById(const std::string &branchId, const std::string &newCity);

    /**
     * @brief Set the branch address by branch ID
     * 
     * @param branchId The branch ID to update
     * @param newAdd The new address to set
     */
    void setBranchAddressById(const std::string &branchId, const std::string &newAdd);

    /**
     * @brief Set the branch manager by branch ID
     * 
     * @param branchId The branch ID to update
     * @param newBranchManagerId The new manager ID to assign
     */
    void setBranchManagerById(const std::string &branchId, const std::string &newBranchManagerId);

    /**
     * @brief Add a new branch to the database
     * 
     * @param branchId The unique branch ID
     * @param newName The branch name
     * @param newCity The city where the branch is located
     * @param newAdd The branch address
     * @param newBranchManagerId The manager ID for the branch
     */
    void addBranch(const std::string &branchId, const std::string &newName, const std::string &newCity, const std::string &newAdd, const std::string &newBranchManagerId);

    /**
     * @brief Delete a branch from the database
     * 
     * @param branchId The branch ID to delete
     */
    void deleteBranch(const std::string &branchId);

    /**
     * @brief Process incoming messages and perform the requested operation
     * 
     * @param message The JSON message containing operation details
     * @return nlohmann::json The result of the operation
     */
    nlohmann::json processMessage(const nlohmann::json& message) override;
    
};  

} // namespace Banking