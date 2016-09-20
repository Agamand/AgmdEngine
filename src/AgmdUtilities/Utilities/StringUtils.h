/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <Container/Vector.h>
#include <Debug/Exception.h>


namespace AgmdUtilities
{

    void Split(const std::string& str, a_vector<std::string>& tokens, const std::string& delim = " \t\n");

    std::string ReadFile(const std::string& filename);

    unsigned long StringHash(const std::string& string);

    std::string ToLower(const std::string& txt);

    std::string ToUpper(const std::string& txt);


    class StringBuilder
    {
    public :

        StringBuilder();

        template <typename T> StringBuilder(const T& value);

        template <typename T> StringBuilder& operator ()(const T& value);

        operator std::string();

    private :

        std::ostringstream m_OutStream;
    };

    class StringExtractor
    {
    public :

        StringExtractor(const std::string& txt);

        template <typename T> StringExtractor& operator ()(T& value);

        void ThrowIfEOF();

    private :

        std::istringstream m_InStream;
    };

    #include "StringUtils.inl"


}


#endif // STRINGUTILS_H
