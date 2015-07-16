#version 330

#include "global_uniform.glsl"
#include "math.glsl"
#include "color_utils.glsl"
#ifdef _VERTEX_

uniform mat4 u_matProjectionPlane;
uniform int u_particleCount;
uniform float u_yoffset;
uniform sampler2D texture0;
uniform sampler2D texture1;

in float in_Vertex;
out float v_life;
out float v_color;

const float size = 20.0f;
void main()
{
	float offset = (1+in_Vertex)*1/float(u_particleCount);
	vec4 pos = vec4(texture(texture0,vec2(offset,u_yoffset)).rgb/1000.f,1);
	vec4 extra = vec4(texture(texture1,vec2(offset,u_yoffset)).rgb,1);
	
	v_life =1.0f; clamp(extra.x*1000,20.f,1000.f);
	v_color = extra.y;
	vec4 viewPos = u_matView*pos;
	float dist = length(viewPos);
	gl_PointSize = clamp(extra.z*200,20,100)/dist;
	gl_Position = u_matProjection*vec4(viewPos.xyz,1);
}
#endif


#ifdef _FRAGMENT_

uniform sampler2D texture2;

in float v_life;
in float v_color;
out vec4 out_Color;

void main()
{
	vec4 tex = texture(texture2,gl_PointCoord).rgba;
	out_Color = vec4(tex.rgb*getColor(v_color),tex.a*v_life);
}



#endif