//
// Example usage of the aegis-log library
// Conditional logging
//

// Disable trace and debug messages in release mode
#ifdef NDEBUG
#define AEGIS_LOG_DISABLE_DEBUG
#define AEGIS_LOG_DISABLE_TRACE
#endif

#include <aegis-log/log.h>
#include <aegis-log/sinks/console_sink.h>

auto main() -> int
{
	Aegis::Log::init(Aegis::Log::Trace) // Show all log messages
		.addSink<Aegis::Log::ConsoleSink>();

	ALOG::fatal("This is a critical message");
	ALOG::warn("This is a warning message");
	ALOG::info("This is an info message");
	ALOG::debug("This is a debug message"); // Will be stripped from release builds
	ALOG::trace("This is a trace message"); // Will be stripped from release builds

	return 0;
}