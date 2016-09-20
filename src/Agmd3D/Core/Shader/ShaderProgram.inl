/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/


template <class T>
inline void ShaderProgram::SetParameter(TMatrixType type, T value) const
{
    m_ShaderProgram->SetParameter(type, value);
}

template <class T>
inline void ShaderProgram::SetParameter(const std::string& name, T value) const
{
    m_ShaderProgram->SetParameter(name,value);
}

template <class T>
inline void ShaderProgram::SetParameter(const std::string& name, T value, a_uint32 count) const
{
    m_ShaderProgram->SetParameter(name,value,count);
}

template <class T> 
inline void SetParameter(const std::string& name, Buffer<T> buf)
{
    //DO NOTHING;
}
/*
template <> 
inline void SetParameter(std::string name, Buffer<G> buf)
{
    //DO NOTHING;
}*/

inline void ShaderProgram::Enable()  const
{
    m_ShaderProgram->Use(true);
}

inline void ShaderProgram::Disable() const
{
    m_ShaderProgram->Use(false);
}