#version 330
#ifdef _VERTEX_
#include <common/global_uniform.glsl>

   layout(location = 0)in vec3 in_Vertex;
   void main()                  
   {                            
      gl_Position = u_matViewProjection*vec4(in_Vertex,1);
   }                            
#endif

#ifdef _FRAGMENT_
   out vec4 out_color;

   void main()                                  
   {                   
     out_color = vec4(1,0,0,1); 
   }
#endif