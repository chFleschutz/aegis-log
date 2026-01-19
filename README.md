# Aegis-Log

Simple and fast header-only C++20 logging library with no dependencies.

![aegis-log-console](https://github.com/user-attachments/assets/667fea57-cf1a-4dbd-a289-bf36af990a4e)

## Features

- Header-only
- Stream-style logging
- Format-string-style logging
- Thread-safe
- Asynchronous logging for improved performance
- Runtime log filtering
- Easily exclude specific log levels from builds
- Log to multiple destinations
- Support for multiple loggers
- Custom sink support for logging to custom destinations
- Custom formatter support

## Getting Started

The library requires a C++20 compiler. 

Since it's header-only, simply copy the [include](include/) folder to your project.

Alternatively you can add the library using cmake to automatically set the include paths:

1. Clone the repo to your desired location

```bash
git clone https://github.com/chFleschutz/aegis-log.git
```

2. Add the subdirectory of the library in your projects `CMakeLists.txt` file and link it to your target

```cmake
add_subdirectory(aegis-log)
target_link_libraries(MyProject PRIVATE Aegis::Log)
```

## Usage Examples

See the [examples](examples/) folder for full example projects.

**Basic usage**

```cpp
#include <aegis-log/log.h>
#include <aegis-log/sinks/console_sink.h>

int main()
{
	// Initialize default logger
	Aegis::Log::init(Aegis::Log::Trace) // Show all log messages
		.addSink<Aegis::Log::ConsoleSink>();

	// Stream style logging
	ALOG::fatal() << "This is a fatal message";
	ALOG::warn() << "This is a warn message";
	ALOG::info() << "This is an info message";
	ALOG::debug() << "This is a debug message";
	ALOG::trace() << "This is a trace message";

	// Format string style logging
	ALOG::fatal("This is a fatal message");
	ALOG::warn("This is a warn message");
	ALOG::info("This is a info message");
	ALOG::debug("This is a debug message");
	ALOG::trace("This is a trace message");

	// Formatted logging
	ALOG::info() << "The answer is " << 42;
	ALOG::info("The answer is indeed {}", 42);
}
```

**Adding more Sinks**
```cpp
#include <aegis-log/log.h>
#include <aegis-log/sinks/console_sink.h>
#include <aegis-log/sinks/file_sink.h>

int main()
{
	Aegis::Log::init(Aegis::Severity::Trace) // Show all logs 
		.addSink<Aegis::ConsoleSink>()
		.addSink<Aegis::FileSink>("log.txt");

	// Printed in both the console and the log file
	ALOG::info("Hello World");
}
```

**Creating multiple loggers**
```cpp
#include <aegis-log/log.h>
#include <aegis-log/sinks/console_sink.h>
#include <aegis-log/sinks/file_sink.h>

// Optional: create enum for IDs
enum LogID
{
	Default = Aegis::Log::DEFAULT_LOGGER,
	Secondary
};

auto main() -> int
{
	// Default logger
	Aegis::Log::init(Aegis::Log::Trace) // Show all logs
		.addSink<Aegis::Log::ConsoleSink>();

	// Secondary logger
	Aegis::Log::init<Secondary>(Aegis::Log::Severity::Fatal) // Show only fatal logs
		.addSink<Aegis::Log::ConsoleSink>()
		.addSink<Aegis::Log::FileSink>("log.txt");

	// Print to default logger
	ALOG::fatal() << "This is a fatal message";
	ALOG::info<Default>() << "This is an info message";
	ALOG::debug<Default>() << "This is a debug message";

	// Print to secondary logger
	ALOG::fatal<Secondary>() << "Fatal message to secondary log";
	ALOG::warn<Secondary>() << "Warn message to secondary log"; // Excluded
}
```

**Exclude logs from release build**
```cpp
// Disable trace and debug messages in release mode
#ifdef NDEBUG
#define AEGIS_LOG_DISABLE_DEBUG
#define AEGIS_LOG_DISABLE_TRACE
#endif

#include <aegis-log/log.h>
#include <aegis-log/sinks/console_sink.h>

auto main() -> int
{
	Aegis::Log::init(Aegis::Log::Trace) 
		.addSink<Aegis::Log::ConsoleSink>();

	ALOG::fatal("This is a critical message");
	ALOG::warn("This is a warning message");
	ALOG::info("This is an info message");
	ALOG::debug("This is a debug message"); // Will be stripped from release builds
	ALOG::trace("This is a trace message"); // Will be stripped from release builds
}
```

**Custom log threads**
```cpp
#include <aegis-log/log.h>
#include <aegis-log/sinks/console_sink.h>

auto main() -> int
{
	// Logger 0 uses the current thread for logging
	Aegis::Log::init<0, Aegis::Log::NO_THREAD>(Aegis::Log::Trace)
		.addSink<Aegis::Log::ConsoleSink>();

	// Logger 1 uses a separate thread with ID 1
	Aegis::Log::init<1, 1>(Aegis::Log::Trace) 
		.addSink<Aegis::Log::ConsoleSink>();

	// Logger 2 uses a separate thread with ID 1 (same thread as Logger 1)
	Aegis::Log::init<2, 1>(Aegis::Log::Trace)
		.addSink<Aegis::Log::ConsoleSink>();
}
```
