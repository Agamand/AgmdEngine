inline void Split(const std::string& str, std::vector<std::string>& tokens, const std::string& delim)
{
    tokens.clear();

    for (std::string::size_type p1 = 0, p2 = 0; p1 != std::string::npos; )
    {
        p1 = str.find_first_not_of(delim, p1);
        if (p1 != std::string::npos)
        {
            p2 = str.find_first_of(delim , p1);
            tokens.push_back(str.substr(p1, p2 - p1));
            p1 = p2;
        }
    }
}

inline std::string ReadFile(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file)
        throw LoadingFailed(filename, "Impossible d'accéder au fichier en lecture");

    std::ostringstream oss;
    oss << file.rdbuf();

    return oss.str();
}

inline unsigned long StringHash(const std::string& str)
{
    unsigned long ret = 0;
    for (std::string::const_iterator i = str.begin(); i != str.end(); ++i)
        ret = 5 * ret + *i;

    return ret;
}

inline std::string ToLower(const std::string& txt)
{
    std::string Ret(txt.size(), ' ');

    std::transform(txt.begin(), txt.end(), Ret.begin(), static_cast<int (*)(int)>(std::tolower));

    return Ret;
}

inline std::string ToUpper(const std::string& txt)
{
    std::string Ret(txt.size(), ' ');

    std::transform(txt.begin(), txt.end(), Ret.begin(), static_cast<int (*)(int)>(std::toupper));

    return Ret;
}

inline StringBuilder::StringBuilder()
{

}

template <typename T>
inline StringBuilder::StringBuilder(const T& value)
{
    m_OutStream << value;
}

template <typename T>
inline StringBuilder& StringBuilder::operator ()(const T& value)
{
    m_OutStream << value;

    return *this;
}

inline StringBuilder::operator std::string()
{
    return m_OutStream.str();
}

inline StringExtractor::StringExtractor(const std::string& txt) :
m_InStream(txt)
{

}

template <typename T>
inline StringExtractor& StringExtractor::operator ()(T& value)
{
    if (!(m_InStream >> value))
    {
        if (m_InStream.eof())
            throw BadConversion(StringBuilder("Tentative d'extraire un \"")(typeid(T).name())("\" à partir d'une chaîne vide"));
        else
            throw BadConversion(StringBuilder("Impossible de convertir de \"string\" en \"")(typeid(T).name())("\""));
    }

    return *this;
}

inline void StringExtractor::ThrowIfEOF()
{
    std::string Left;
    if (std::getline(m_InStream, Left))
        throw BadConversion("Chaîne trop longue, \"" + Left + "\" n'a pas été extrait");
}
