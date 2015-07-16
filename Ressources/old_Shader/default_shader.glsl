#version 330
uniform float u_time;
#ifdef _VERTEX_
   layout(location = 0)in vec3 in_Vertex;
   float PI = 3.14159265359;
   void main()                  
   {                            
      gl_Position = vec4(in_Vertex,1);
   }                            
#endif

#ifdef _FRAGMENT_
   out vec4 out_color;

   void main()                                  
   {                   
     out_color = vec4(1); 
   }
#endif