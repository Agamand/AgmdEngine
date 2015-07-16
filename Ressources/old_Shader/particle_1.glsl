#version 330

#include "global_uniform.glsl"
#include "math.glsl"


#ifdef _VERTEX_

uniform mat4 u_matProjectionPlane;
in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_TexCoord;
out vec4 v_emitter_pos;
void main()
{
	v_emitter_pos = u_matModel * vec4(0.0f,0.0f,0.0f, 1.0f);
	v_TexCoord = in_Vertex.xy;
	gl_Position = u_matProjectionPlane*vec4(in_Vertex,1.0f);
}
#endif


#ifdef _FRAGMENT_

uniform int u_time_diff=1;
uniform int u_seed;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 v_TexCoord;
in vec4 v_emitter_pos;

layout(location = 0) out vec3 out_Position;
layout(location = 1) out vec3 out_Velocity;
layout(location = 2) out vec3 out_Extra;




void main()
{
	float time = u_time_diff;
	float rand = rand1f(v_TexCoord,u_seed); //104
	float rand2 = rand1f(v_TexCoord,u_seed+585764);
	float rand3 = rand1f(v_TexCoord,u_seed-654558);
	float rand4 = rand1f(v_TexCoord,u_seed+56554);
	vec4 extra = texture(texture2,vec2(v_TexCoord.x,v_TexCoord.y));
	vec3 velocity = texture(texture1,vec2(v_TexCoord.x,v_TexCoord.y)).rgb;
	vec3 position = texture(texture0,vec2(v_TexCoord.x,v_TexCoord.y)).rgb;
	if(extra.x <= 0)	
	{
		float speed = 0.03f+0.06f*rand2;
		speed *=2;
		extra.x = 0.7f;
		extra.y = rand4;
		out_Extra = vec3(extra.x,extra.y,0);
		out_Position = v_emitter_pos.xyz;
		out_Velocity = vec3(speed*cos(rand*M_PI*2),speed*sin(rand*M_PI*2),0);

	}else
	{
		out_Extra =  vec3(extra.x-0.01f,extra.y,0);
		velocity -= vec3(0,0.0002f*time/2,0);
		out_Velocity = velocity;// - vec3(0,0.01,0)*time;//vec3(velocity);
		out_Position = position+ velocity*time;
	}
}



#endif