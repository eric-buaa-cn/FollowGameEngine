#include <MyLogger.h>

#include <spdlog/sinks/stdout_color_sinks.h>

// This header is related to file rotating logger.
// #include <spdlog/sinks/rotating_file_sink.h>

MyLogger::MyLogger() {
    spdlog::set_pattern("[%Y-%m-%d %T.%e] [%n] [%^%L%$] [%s:%#:%!] [thread %t] %v");

    // This line creates a console logger.
    auto logger = spdlog::stdout_color_mt("app");

    // This line creates a file rotating logger.
    // auto logger = spdlog::rotating_logger_mt("file_logger", "mylog.txt", 1024 * 1024 * 5, 3);

    // Contorl the log level at runtime.
    logger->set_level(spdlog::level::trace);
    spdlog::set_default_logger(logger);
}