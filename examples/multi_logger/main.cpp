//
// Example usage of the aegis-log library
// Multiple loggers
//

#include <aegis-log/log.h>
#include <aegis-log/sinks/console_sink.h>
#include <aegis-log/sinks/file_sink.h>

// Define custom log IDs
enum LogID
{
	DefaultLog = Aegis::Log::DEFAULT_LOGGER,
	SecondaryLog
};

auto main() -> int
{
	// Default logger
	Aegis::Log::init(Aegis::Log::Trace) // Show all log messages
		.addSink<Aegis::Log::ConsoleSink>();

	// Secondary logger
	std::filesystem::path logFile = std::filesystem::current_path() / "log.txt";
	Aegis::Log::init<SecondaryLog>(Aegis::Log::Severity::Info) // 
		.addSink<Aegis::Log::ConsoleSink>()
		.addSink<Aegis::Log::FileSink>(logFile);

	// Print to default logger
	ALOG::info() << "Secondary log file: " << logFile;
	ALOG::fatal() << "This is a fatal message";
	ALOG::info<DefaultLog>() << "This is an info message";
	ALOG::debug<DefaultLog>() << "This is a debug message";

	// Print to secondary logger
	ALOG::fatal<SecondaryLog>() << "Fatal message to secondary log";
	ALOG::warn<SecondaryLog>() << "Warn message to secondary log";
	ALOG::info<SecondaryLog>() << "Info message to secondary log";

	return 0;
}