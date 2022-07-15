#include "Logging.h"
#include "snowpch.h"

#include <cstdarg>

Snow::Logging::Logging()
{
}

Snow::Logging::~Logging()
{
}

void Snow::Logging::Log(LogLevel level, const char* message, ...)
{
	const char* logLevelName = LogLevelToString(level);
	char out[5000];
	memset(out, 0, sizeof(out));
	va_list argPtr;
	va_start(argPtr, message);
	vsnprintf(out, 10000, message, argPtr);
	va_end(argPtr);

	char outMsg[5000];
	sprintf_s(outMsg, "[%s]: %s\n", logLevelName, out);

	printf("%s", outMsg);
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
