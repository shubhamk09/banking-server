/**
 * @file Logger.cpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Implementation of Logger class for banking system
 * @version 0.1
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <filesystem>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

std::shared_ptr<spdlog::logger> Banking::Logger::s_Logger;

/**
 * @brief 
 * 
 */
std::string Banking::Logger::GetLogDirectory() {
    // Check for custom log directory from environment variable
    const char* custom_log_dir = std::getenv("BANKING_LOG_DIR");
    if (custom_log_dir && std::strlen(custom_log_dir) > 0) {
        return std::string(custom_log_dir);
    }
    
#ifdef _WIN32
    // Windows: Use C:\banking-system-logs
    return "C:\\banking-system-logs";
#else
    // Linux/Unix: Use /tmp/banking-system-logs
    return "/tmp/banking-system-logs";
#endif
}

void Banking::Logger::Init() {
    spdlog::set_pattern("[%^%L%$] %v");
    if (!s_Logger)
    {
        try {
            // Get platform-appropriate log directory
            std::string logs_dir = GetLogDirectory();
            std::string log_path = logs_dir + "/banking-system.log";
            
            // Create logs directory if it doesn't exist (with proper permissions)
            std::filesystem::create_directories(logs_dir);
            
            s_Logger = spdlog::basic_logger_mt("banking_logger", log_path, true);
            s_Logger->set_level(spdlog::level::debug);
            s_Logger->flush_on(spdlog::level::debug); // Force flush on all messages
            s_Logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [PID:%P] [TID:%t] %v");
            s_Logger->info("Banking system logger initialized - centralized logging to {}", log_path);
            s_Logger->info("Log directory: {}", logs_dir);
        } catch (const std::exception& e) {
            // Fallback to console logger if file logger fails
            s_Logger = spdlog::stdout_color_mt("banking_console");
            s_Logger->set_level(spdlog::level::debug);
            s_Logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
            s_Logger->error("Failed to initialize file logger: {}. Using console logger instead.", e.what());
        }
    }
}

/**
 * @brief 
 * 
 * @return std::shared_ptr<spdlog::logger>& 
 */
std::shared_ptr<spdlog::logger>& Banking::Logger::GetLogger() {
    return s_Logger;
}
