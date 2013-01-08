
#include <Debug\Exception.h>
#include <Debug\Logger.h>
#include <Utilities\StringUtils.h>

namespace AgmdUtilities
{
    Exception::Exception(const std::string& msg) : m_Msg(msg)
    {
        Logger::Log(LOGNORMAL,m_Msg.c_str());
    }

    Exception::~Exception() throw()
    {}

    const char* Exception::what() const throw()
    {
        return m_Msg.c_str();
    }

    AssertException::AssertException(const std::string& file, int line, const std::string& msg)
    {}

    BadDelete::BadDelete(const void* ptr, const std::string& file, int line, bool newArray) :    Exception(StringBuilder("Anomalie ")((newArray ? "new[] / delete" :  "new / delete[]"))(" detectee")("\n")("Adresse : 0x")(ptr)("\nFichier source : ")(file)(" (")(line)(")"))
    {}

    LoadingFailed::LoadingFailed(const std::string& File, const std::string& Message) : Exception(StringBuilder("Erreur dans le chargement de ")(File)("")(Message))
    {}

    OutOfMemory::OutOfMemory(const std::string& msg) : Exception(msg)
    {}

    Unsupported::Unsupported(const std::string& function) : Exception(StringBuilder("Fonctionnalité non supportée")("")(function))
    {}

    BadConversion::BadConversion(const std::string& error) : Exception(error)
    {}
}
