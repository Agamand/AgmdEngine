#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <Config/Export.h>

#include <Matrix4.h>
#include <stack>

namespace Agmd
{
    class AGMD_EXPORT MatStack
    {
    public:
        static void push(mat4 matrix);
        static void pop();
        static mat4 get();
        static void set(mat4 matrix);
    private:
        MatStack();
        ~MatStack();

        static MatStack& Instance();

        std::stack<mat4> m_matStack;

        static MatStack* m_instance;
    };
}


#endif /*MATRIXSTACK_H*/