
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstdlib>
#include <exception>
#include <string>

namespace AgmdUtilities
{
	class Exception : public std::exception
	{
	public :

		Exception(const std::string& msg = "");

		virtual ~Exception() throw();

		virtual const char* what() const throw();

	protected :

		std::string m_Msg;
	};

	struct AssertException : public Exception
	{
		AssertException(const std::string& file, int line, const std::string& msg);
	};

    #ifdef _DEBUG
    #   define Assert(condition) if (!(condition)) throw AssertException(__FILE__, __LINE__, "Condition error\n" #condition)
    #else
        inline void DoNothing(bool) {}
    #   define Assert(condition) DoNothing(!(condition))
    #endif

	struct BadDelete : public Exception
	{
		BadDelete(const void* ptr, const std::string& file, int line, bool newArray);
	};

	struct LoadingFailed : public Exception
	{
		LoadingFailed(const std::string& file, const std::string& msg);
	};

	struct OutOfMemory : public Exception
	{
		OutOfMemory(const std::string& msg);
	};

    struct Unsupported : public Exception
    {
        Unsupported(const std::string& function);
    };

    struct BadConversion : public Exception
    {
        BadConversion(const std::string& error);
    };
}

#endif //EXCEPTION_H