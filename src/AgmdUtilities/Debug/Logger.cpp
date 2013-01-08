#include "Logger.h"
#include <iostream>
#include <cassert>
#include <cstdarg>
#include <ctime>

SINGLETON_IMPL(AgmdUtilities::Logger);

namespace AgmdUtilities
{
	

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
		char sBuffer[4096];
		va_list params;
 		va_start(params, format);
		vsnprintf_s(sBuffer, 4096, format, params);
		//vsprintf_s(sBuffer, format, params);
		va_end(params);

		Logger::Instance().Write(sBuffer);
	}
	
	void Logger::Write(const std::string& msg)
	{
		m_File << /*CurrentDate() << CurrentTime() << " " <<*/ msg << "\n";
	}

	void Logger::SetFilename(std::string name)
	{
		m_File.close();
		m_File = std::ofstream(name + ".log");
	}

	std::string Logger::CurrentDate() const
	{
		// Récupération et formatage de la date
		char sTime[24];
		time_t CurrentTime = time(NULL);
		strftime(sTime, sizeof(sTime), "[%d/%m/%Y]", localtime(&CurrentTime));

		return sTime;
	}
	std::string Logger::CurrentTime() const
	{
		// Récupération et formatage de la date
		char sTime[24];
		time_t CurrentTime = time(NULL);
		strftime(sTime, sizeof(sTime), "[%H:%M:%S]", localtime(&CurrentTime));

		return sTime;
	}
}