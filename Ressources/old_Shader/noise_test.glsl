#version 330
uniform float u_time;
#ifdef _VERTEX_
   layout(location = 0)in vec3 in_Vertex;
   out vec3 pos;
   float PI = 3.14159265359;
   void main()                  
   {               
      pos = -vec3(1,1,0)+in_Vertex*2;             
      gl_Position = vec4(pos,1);
   }                            
#endif

#ifdef _FRAGMENT_

uniform int u_seed;
uniform float u_g;
uniform int u_o;
uniform float u_l;
   in vec3 pos;
   out vec4 out_color;
#include "noise_function.glsl"
//#include "perlin_noise_function.glsl"
#include "color_utils.glsl"
   void main()                                  
   {
     vec2 qq;
     vec2 r;
     float color = pattern2(pos.xy,qq,r,u_l,u_g,u_time/4.f);                   
     //float color = GetHeight(pos.x*0.1,pos.y*0.1,u_g,u_l,u_o,u_seed);
     out_color = vec4(vec3(color),1); //
   }
#endif