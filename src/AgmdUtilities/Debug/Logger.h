
#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <string>
#include <Utilities\Singleton.h>
#include <fstream>


namespace AgmdUtilities
{
	enum LogLevel
	{
		LOGNORMAL,
		LOGERROR,
		LOGDEBUG
	};

    class Logger : public Singleton<Logger>
    {
	MAKE_SINGLETON(Logger);
    public :
		Logger();
        ~Logger();
        static void Log(LogLevel loglevel,const char* format, ...);
		void SetFilename(std::string name);

    protected :

        std::string CurrentDate() const;
        std::string CurrentTime() const;

    private :

        void Write(const std::string& msg);
		std::ofstream m_File;
    };

	#define LOG(msg, ...) Logger::Log(LOGNORMAL, msg, ...)
	#define ERROR_LOG(msg, ...) Logger::Log(LOGERROR, msg, ...)
	#define DEBUG_LOG(msg, ...) Logger::Log(LOGDEBUG, msg, ...)

}


#endif // LOGGER_H
