#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;

out vec4 ShadowCoord;


void main()
{
	mat4 bias = mat4(0.5,0.0,0.0,0.0
					 0.0,0.5,0.0,0.0
					 0.0,0.0,0.5,0.0
					 0.5,0.5,0.5,1.0);

    ShadowCoord= bias*u_matProjection*u_matView*u_matModel*vec4(in_Vertex, 1.0);
	gl_Position = u_matProjection*u_matView*u_matModel*vec4(in_Vertex, 1.0);
}
#endif

#ifdef _FRAGMENT_
uniform sampler2D texture3;

in vec4 ShadowCoord;
out out_Color;
void main()
{	
	vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w ;
	
	// Used to lower moiré pattern and self-shadowing
	shadowCoordinateWdivide.z += 0.0005;
	
	
	float distanceFromLight = texture2D(ShadowMap,shadowCoordinateWdivide.st).z;
	
	
 	float shadow = 1.0;
 	if (ShadowCoord.w > 0.0)
 		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;
  	
	
  	out_Color =	 shadow * gl_Color;
  
}

#endif