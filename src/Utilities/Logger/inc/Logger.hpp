/**
 * @file Logger.hpp
 * @author Shubham Kalihari (shubhamkalihari09@gmail.com)
 * @brief Logging utilities and macros for banking system
 * @version 0.1
 * @date 2023-08-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BANKING_LOGGER_HPP
#define BANKING_LOGGER_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>


namespace Banking{
    /**
     * @brief Singleton logger class for the banking system
     * 
     * This class provides a centralized logging mechanism using spdlog library.
     * It supports file-based logging with different log levels and thread-safe operations.
     */
    class Logger {
    public:
        /**
         * @brief Initialize the logger system
         * 
         * Sets up the logger with file output and debug level.
         * This method should be called once at application startup.
         */
        static void Init();

        /**
         * @brief Get the logger instance
         * 
         * @return std::shared_ptr<spdlog::logger>& Reference to the logger instance
         */
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger; ///< Static logger instance
        
        /**
         * @brief Get the platform-appropriate log directory
         * 
         * @return std::string Path to the log directory
         */
        static std::string GetLogDirectory();
    };

}

// Convenient logging macros for the banking system
#define BANKING_LOGGER_INFO(...)    ::Banking::Logger::GetLogger()->info(__VA_ARGS__)
#define BANKING_LOGGER_ERROR(...)    ::Banking::Logger::GetLogger()->error("[{}:{} {}] ", __FILE__, __LINE__, __FUNCTION__); ::Banking::Logger::GetLogger()->error(__VA_ARGS__)
#define BANKING_LOGGER_WARN(...)    ::Banking::Logger::GetLogger()->warn(__VA_ARGS__)
#endif //BANKING_LOGGER_HPP