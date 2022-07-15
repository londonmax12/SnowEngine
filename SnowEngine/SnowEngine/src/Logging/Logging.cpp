#include "Logging.h"
#include "snowpch.h"

#include "src/Platform/Platform.h"
#include <cstdarg>

Snow::Logging::Logging()
{
}

Snow::Logging::~Logging()
{
}

void Snow::Logging::Log(LogLevel level, const char* message, ...)
{
	bool isError = (level == LogLevel::LOG_LFATAL || level == LogLevel::LOG_LERROR);
	const char* logLevelName = LogLevelToString(level);
	const int msgSize = 5000;
	char out[msgSize];
	memset(out, 0, sizeof(out));
	va_list argPtr;
	va_start(argPtr, message);
	vsnprintf(out, msgSize, message, argPtr);
	va_end(argPtr);

	char outMsg[msgSize];
	sprintf_s(outMsg, "[%s]: %s\n", logLevelName, out);

	if (isError) {
		platform_ConsoleWriteError(outMsg, level);
	}
	else {
		platform_ConsoleWrite(outMsg, level);
	}
}

const char* Snow::Logging::LogLevelToString(LogLevel level)
{
	switch (level)
	{
	case Snow::Logging::LOG_LFATAL:
		return "FATAL";
		break;
	case Snow::Logging::LOG_LERROR:
		return "ERROR";
		break;
	case Snow::Logging::LOG_LWARN:
		return "WARN";
		break;
	case Snow::Logging::LOG_LINFO:
		return "INFO";
		break;
	case Snow::Logging::LOG_LDEBUG:
		return "DEBUG";
		break;
	case Snow::Logging::LOG_LTRACE:
		return "TRACE";
		break;
	default:
		return "";
		break;
	}
}
