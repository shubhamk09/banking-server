/**
 * @file driver.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DatabaseOperations.hpp"

int main(int argc, char** argv)
{
    
    try
    {
        Banking::connection_shptr ptr{std::make_shared<Banking::Connection>()};
        Banking::DatabaseOperations dbO(ptr);
        std::string empid{"MYS00101"};
        std::cout<<dbO.getEmployeeNameById(empid)<<std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    
    return (0);
}