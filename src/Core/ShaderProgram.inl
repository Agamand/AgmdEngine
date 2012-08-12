
template <class T>
inline void ShaderProgram::SetParameter(std::string name, T value)
{
	m_ShaderProgram->SetParameter(name,value);
}

inline void ShaderProgram::Enable()
{
	m_ShaderProgram->Use(true);
}

inline void ShaderProgram::Disable()
{
	m_ShaderProgram->Use(false);
}