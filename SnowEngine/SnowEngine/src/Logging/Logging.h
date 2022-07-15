#pragma once

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0

#if _DEBUG
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#endif

#define SNOW_FATAL(message, ...) Snow::Logging::Log(Snow::Logging::LOG_LFATAL, message, ##__VA_ARGS__)
#define SNOW_ERROR(message, ...) Snow::Logging::Log(Snow::Logging::LOG_LERROR, message, ##__VA_ARGS__)

#ifdef LOG_WARN_ENABLED == 1
#define SNOW_WARN(message, ...) Snow::Logging::Log(Snow::Logging::LOG_LWARN, message, ##__VA_ARGS__)
#else
#define SNOW_WARN(message, ...)
#endif

#ifdef LOG_INFO_ENABLED == 1
#define SNOW_INFO(message, ...) Snow::Logging::Log(Snow::Logging::LOG_LINFO, message, ##__VA_ARGS__)
#else
#define SNOW_INFO(message, ...)
#endif

#ifdef LOG_DEBUG_ENABLED == 1
#define SNOW_DEBUG(message, ...) Snow::Logging::Log(Snow::Logging::LOG_LDEBUG, message, ##__VA_ARGS__)
#else
#define SNOW_DEBUG(message, ...)
#endif

#ifdef LOG_TRACE_ENABLED == 1
#define SNOW_TRACE(message, ...) Snow::Logging::Log(Snow::Logging::LOG_LTRACE, message, ##__VA_ARGS__)
#else
#define SNOW_TRACE(message, ...)
#endif
#include <string>

namespace Snow {
	class Logging
	{
	public:
		Logging();
		~Logging();

		enum LogLevel {
			LOG_LFATAL,
			LOG_LERROR,
			LOG_LWARN,
			LOG_LINFO,
			LOG_LDEBUG,
			LOG_LTRACE
		};
		static void Log(LogLevel level, const char* message, ...);
	private:
		static const char* LogLevelToString(LogLevel level);
	};
}