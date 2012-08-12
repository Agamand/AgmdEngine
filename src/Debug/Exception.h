
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstdlib>
#include <exception>
#include <string>
#include <Config/Export.h>

namespace Agmd
{
	class AGMD_EXPORT Exception : public std::exception
	{
	public :

		Exception(const std::string& msg = "");

		virtual ~Exception() throw();

		virtual const char* what() const throw();

	protected :

		std::string m_Msg;
	};

	struct AGMD_EXPORT AssertException : public Exception
	{
		AssertException(const std::string& file, int line, const std::string& msg);
	};

    #ifdef _DEBUG
    #   define Assert(condition) if (!(condition)) throw AssertException(__FILE__, __LINE__, "Condition error\n" #condition)
    #else
        inline void DoNothing(bool) {}
    #   define Assert(condition) DoNothing(!(condition))
    #endif

	struct AGMD_EXPORT BadDelete : public Exception
	{
		BadDelete(const void* ptr, const std::string& file, int line, bool newArray);
	};

	struct AGMD_EXPORT LoadingFailed : public Exception
	{
		LoadingFailed(const std::string& file, const std::string& msg);
	};

	struct AGMD_EXPORT OutOfMemory : public Exception
	{
		OutOfMemory(const std::string& msg);
	};

    struct AGMD_EXPORT Unsupported : public Exception
    {
        Unsupported(const std::string& function);
    };

    struct AGMD_EXPORT BadConversion : public Exception
    {
        BadConversion(const std::string& error);
    };
}

#endif //EXCEPTION_H