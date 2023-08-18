/**
 * @file Logger.hpp
 * @author your name (you@domain.com)
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
        static void Init(){
            spdlog::set_pattern("[%^%L%$] %v");
            s_Logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt", true);
            s_Logger->set_level(spdlog::level::debug);
        }

        inline static std::shared_ptr<spdlog::logger>& GetLogger(){return s_Logger;}

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
    std::shared_ptr<spdlog::logger> Logger::s_Logger;
}
#endif //BANKING_LOGGER_HPP