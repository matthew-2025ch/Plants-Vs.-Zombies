#include "Logger.hpp"
auto Logger::Initialize()->void {
	std::filesystem::create_directories("logs");
	std::vector<spdlog::sink_ptr>sinks;
#ifdef _DEBUG
	std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> consoleSink
		= std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_level(spdlog::level::debug);
	sinks.push_back(consoleSink);
#endif
	std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> fileSink
		= std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/pvz.log", 5 * 1024 * 1024, 3);
#ifdef _DEBUG
	fileSink->set_level(spdlog::level::debug);
#else
	fileSink->set_level(spdlog::level::info);
#endif
	sinks.push_back(fileSink);
	std::shared_ptr<spdlog::logger>logger = std::make_shared<spdlog::logger>("PVZ", sinks.begin(), sinks.end());
	logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
#ifdef _DEBUG
	logger->set_level(spdlog::level::debug);
#else
	logger->set_level(spdlog::level::info);
#endif
	logger->flush_on(spdlog::level::warn);
	spdlog::set_default_logger(logger);
	spdlog::info("Logger Initialized");
}
auto Logger::Flush()->void {
	spdlog::default_logger()->flush();
}