#pragma once

namespace Log
{
	enum class Level
	{
		Info,
		Warning,
		Error
	};

	void LogMessage(Level level, const char* message);
	void LogMessage(Level level, const char* message, const char* file, int line);
	void LogMessage(Level level, const char* message, const char* file, int line, const char* function);
}