#include <Core/MatStack.h>


namespace Agmd
{
    MatStack::MatStack()
    {
        m_matStack.push(mat4(1.0f));
    }

    MatStack::~MatStack()
    {}

    void MatStack::push(mat4 _matrix)
    {
        mat4 matrix = Instance().get()*_matrix;
        Instance().m_matStack.push(matrix);
    }

    void MatStack::pop()
    {
        Instance().m_matStack.pop();
    }

    mat4 MatStack::get()
    {
        return Instance().m_matStack.top();
    }

    void MatStack::set(mat4 _matrix)
    {
        Instance().m_matStack.top() = _matrix;
    }

    MatStack& MatStack::Instance()
    {
        if(!m_instance)
            m_instance = new MatStack();

        return *m_instance;
    }

    MatStack* MatStack::m_instance = NULL;
}