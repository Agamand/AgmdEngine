
template <class T>
inline void ShaderProgram::SetParameter(TMatrixType type, T value)
{
	m_ShaderProgram->SetParameter(type, value);
}

template <class T>
inline void ShaderProgram::SetParameter(std::string name, T value)
{
	m_ShaderProgram->SetParameter(name,value);
}

template <class T>
inline void ShaderProgram::SetParameter(std::string name, T value, uint32 count)
{
	m_ShaderProgram->SetParameter(name,value,count);
}

inline void ShaderProgram::Enable()
{
	m_ShaderProgram->Use(true);
}

inline void ShaderProgram::Disable()
{
	m_ShaderProgram->Use(false);
}