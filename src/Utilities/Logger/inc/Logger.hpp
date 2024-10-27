/**
 * @file Logger.hpp
 * @author Shbham Kalihari (shubhamkalihari09@gmail.com)
 * @brief 
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
    class Logger {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };

}
#define BANKING_LOGGER_INFO(...)    ::Banking::Logger::GetLogger()->info(__VA_ARGS__)
#define BANKING_LOGGER_ERROR(...)    ::Banking::Logger::GetLogger()->error("[{}:{} {}] ", __FILE__, __LINE__, __FUNCTION__); ::Banking::Logger::GetLogger()->error(__VA_ARGS__)
#define BANKING_LOGGER_WARN(...)    ::Banking::Logger::GetLogger()->warn(__VA_ARGS__)
#endif //BANKING_LOGGER_HPP