#pragma once

#include "aegis-log/formatter/formatter.h"
#include "aegis-log/log_entry.h"

namespace Aegis::Log
{
	class LogSink
	{
	public:
		LogSink(std::unique_ptr<Log::Formatter> formatter) : m_formatter(std::move(formatter)) {}
		LogSink(const LogSink&) = delete;
		LogSink(LogSink&&) = delete;
		virtual ~LogSink() = default;

		auto operator=(const LogSink&) -> LogSink& = delete;
		auto operator=(LogSink&&) -> LogSink& = delete;

		virtual void log(const LogEntry& entry) = 0;

		[[nodiscard]] auto format(const LogEntry& entry) const -> std::string
		{
			return m_formatter->format(entry);
		}

	private:
		std::unique_ptr<Log::Formatter> m_formatter;
	};
} // namespace Aegis::Log