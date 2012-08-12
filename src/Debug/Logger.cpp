#include "Logger.h"
#include <iostream>
#include <cassert>
#include <cstdarg>

namespace Agmd
{
	SINGLETON_IMPL(Logger);

	Logger::Logger() : m_File("agmd.log")
	{
		assert(m_File);
	}


	Logger::~Logger()
	{
		m_File.close();
	}

	void Logger::Log(LogLevel loglevel,const char* format, ...)
	{
		char sBuffer[512];
		va_list params;
		va_start(params, format);
		vsprintf_s(sBuffer, format, params);
		va_end(params);

		Singleton<Logger>::Instance().Write(sBuffer);
	}
	
	void Logger::Write(const std::string& msg)
	{
		m_File << msg;
	}
}