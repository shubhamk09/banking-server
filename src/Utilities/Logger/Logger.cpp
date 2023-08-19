/**
 * @file Logger.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Logger.hpp"

std::shared_ptr<spdlog::logger> Banking::Logger::s_Logger;

/**
 * @brief 
 * 
 */
void Banking::Logger::Init() {
    spdlog::set_pattern("[%^%L%$] %v");
    s_Logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt", true);
    s_Logger->set_level(spdlog::level::debug);
}

/**
 * @brief 
 * 
 * @return std::shared_ptr<spdlog::logger>& 
 */
std::shared_ptr<spdlog::logger>& Banking::Logger::GetLogger() {
    return s_Logger;
}
