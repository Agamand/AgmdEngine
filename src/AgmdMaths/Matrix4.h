/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <CL/opencl.h>

using namespace glm;
/*
struct _cl_context;
struct _cl_kernel;
namespace AgmdMaths
{
    

    class Mat4Op
    {
    public:
        static Mat4Op& Get();
        static void Destroy();

        void mat4_prod(const mat4& m1, const mat4& m2, mat4& r);
        static const char * _mat4prod;
    private:
        Mat4Op();
        ~Mat4Op();

        static Mat4Op*      m_instance;
        cl_context          m_context;
        cl_kernel           m_mat4prod_kernel;
        cl_command_queue    m_command_queue;
    };
    #include "Matrix4.inl"
}
*/
#endif /* _MATRIX4_H_ */
