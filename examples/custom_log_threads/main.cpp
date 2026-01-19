//
// Example usage of the aegis-log library
// Custom log threads
//

#include <aegis-log/log.h>
#include <aegis-log/sinks/console_sink.h>

auto main() -> int
{
	// Logger 0 uses the current thread for logging
	Aegis::Log::init<0, Aegis::Log::NO_THREAD>(Aegis::Log::Trace) //
		.addSink<Aegis::Log::ConsoleSink>();

	// Logger 1 uses a separate thread with ID 1
	Aegis::Log::init<1, 1>(Aegis::Log::Trace) //
		.addSink<Aegis::Log::ConsoleSink>();

	// Logger 2 uses a separate thread with ID 1 (same thread as Logger 1)
	Aegis::Log::init<2, 1>(Aegis::Log::Trace) //
		.addSink<Aegis::Log::ConsoleSink>();
}