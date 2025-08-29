#include "Logger.hpp"
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <spdlog/sinks/basic_file_sink.h>

class LoggerTestFixture : public testing::Test {
protected:
    std::string testLogPath = "test_logs";
    std::string testLogFile = "test_logs/basic-log.txt";
    
    void SetUp() override {
        // Create test logs directory
        if (!std::filesystem::exists(testLogPath)) {
            std::filesystem::create_directories(testLogPath);
        }
        
        // Clean up any existing log file
        if (std::filesystem::exists(testLogFile)) {
            std::filesystem::remove(testLogFile);
        }
    }
    
    void TearDown() override {
        // Clean up test files
        if (std::filesystem::exists(testLogFile)) {
            std::filesystem::remove(testLogFile);
        }
        if (std::filesystem::exists(testLogPath)) {
            std::filesystem::remove(testLogPath);
        }
    }
};

TEST_F(LoggerTestFixture, InitializationTest) {
    // Test logger initialization
    EXPECT_NO_THROW(Banking::Logger::Init());
    
    // Test that logger is not null after initialization
    Banking::Logger::Init();
    auto& logger = Banking::Logger::GetLogger();
    EXPECT_NE(logger, nullptr);
}

TEST_F(LoggerTestFixture, MultipleInitializationTest) {
    // Test that multiple calls to Init() don't cause issues
    EXPECT_NO_THROW({
        Banking::Logger::Init();
        Banking::Logger::Init();
        Banking::Logger::Init();
    });
    
    auto& logger = Banking::Logger::GetLogger();
    EXPECT_NE(logger, nullptr);
}

TEST_F(LoggerTestFixture, GetLoggerTest) {
    Banking::Logger::Init();
    
    auto& logger1 = Banking::Logger::GetLogger();
    auto& logger2 = Banking::Logger::GetLogger();
    
    // Test that GetLogger returns the same instance (singleton behavior)
    EXPECT_EQ(&logger1, &logger2);
    EXPECT_NE(logger1, nullptr);
}

TEST_F(LoggerTestFixture, LoggingFunctionalityTest) {
    Banking::Logger::Init();
    
    // Test basic logging functionality
    EXPECT_NO_THROW({
        BANKING_LOGGER_INFO("Test info message");
        BANKING_LOGGER_WARN("Test warning message");
        BANKING_LOGGER_ERROR("Test error message");
        // Note: BANKING_LOGGER_DEBUG is not defined, so we skip it
    });
}

TEST(LoggerTest, UninitializedLoggerTest) {
    // Test behavior when trying to get logger before initialization
    // This might not crash but should be handled gracefully
    EXPECT_NO_THROW({
        auto& logger = Banking::Logger::GetLogger();
        // Logger might be null if not initialized
        (void)logger; // Suppress unused variable warning
    });
}
