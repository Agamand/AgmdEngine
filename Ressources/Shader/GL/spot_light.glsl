#version 330
#include "global_uniform.glsl"
#include "global_light_uniform.glsl"
#ifdef _VERTEX_

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_texCoord0;
in vec4 in_Tangent;

out vec3 v_Normal;
out vec3 v_Tangent;
out vec3 v_Binormal;
void main()
{
	
	v_Normal = mat3(u_matModel)*in_Normal;
	v_Tangent = in_Tangent.xyz;
	v_Binormal = cross(in_Normal,in_Tangent.xyz)*in_Tangent.w;
	
	gl_Position = u_matProjection*u_matView*u_matModel*vec4(in_Vertex,1.0f); 

}

#endif

#ifdef _FRAGMENT_

in vec3 normal;

void main (void)
{
	
	out_Color = vec4(basecolor);
}

#endif