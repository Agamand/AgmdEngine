

#include <Matrix4.h>

/*
namespace AgmdMaths
{
    Mat4Op* Mat4Op::m_instance = NULL;
    const char* Mat4Op::_mat4prod ="";

    Mat4Op::Mat4Op() :
    m_context(NULL),
    m_command_queue(NULL),
    m_mat4prod_kernel(NULL)
    {
        cl_device_id device_id = NULL;
        cl_platform_id platform_id = NULL;
        cl_uint ret_num_devices;
        cl_uint ret_num_platforms;
        cl_int ret;
        ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
        ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
 
        m_context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
        cl_program program = NULL;
        const size_t src_size = strlen(_mat4prod);
        program = clCreateProgramWithSource(m_context, 1, (const char **)&_mat4prod,
                                        (const size_t *)&src_size, &ret);
        
        ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
        m_mat4prod_kernel = clCreateKernel(program, "_mat4prod", &ret);
        m_command_queue = clCreateCommandQueue(m_context, device_id, 0, &ret);
        m
    }

    Mat4Op::~Mat4Op()
    {
    
    }

    void Mat4Op::Destroy()
    {
        delete m_instance;
        m_instance = NULL;
    }
    
}*/