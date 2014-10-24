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

uniform float u_time_diff=1;
uniform int u_seed;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int u_particleCount;
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
	float rand5 = rand1f(v_TexCoord,u_seed-56554);
	float rand6 = rand1f(v_TexCoord,u_seed-585764);
	
	vec4 extra = texture(texture2,vec2(v_TexCoord.x,v_TexCoord.y));
	vec3 velocity = texture(texture1,vec2(v_TexCoord.x,v_TexCoord.y)).rgb;
	vec3 position = texture(texture0,vec2(v_TexCoord.x,v_TexCoord.y)).rgb;
	if(extra.x <= 0)	
	{
		//+0.06f*rand2;
		float dd = -9000.0f;
		float angle = rand*M_2PI;//-M_PI/2 + (rand-0.5f)*M_2PI;
		
		extra.x = 0.1f+rand3*4.f;
		extra.x /=3.f;
		extra.y=0.f;
		float offset = 1.f/(u_particleCount);
		if(v_TexCoord.x < offset)
		{
			out_Position = v_emitter_pos.xyz-vec3(0,0,0);
			out_Velocity = normalize(vec3(dd*3,0,0))*0.004f;
			extra.y=0.7f;
			extra.z=400.f;
		}/*else if(v_TexCoord.x < offset*2)
		{
			out_Position = v_emitter_pos.xyz+vec3(dd,0,0);
			out_Velocity = -normalize(vec3(dd,0,0))*0.004f;
			extra.y=0.7f;
			extra.z=1000.f;
		}*//*
		else if(v_TexCoord.x < offset*3)
		{
			out_Position = v_emitter_pos.xyz+vec3(0,10000.f,0);
			out_Velocity = vec3(0,-1,0)*0.1f;
			extra.y=0.7f;
			extra.z=900000000.f;
		}*/
		else
		{
			float middle = offset*2+(1-offset*2)/2;
			float rand7 = rand1f(vec2(1,0.5),u_seed+(v_TexCoord.x < middle ? 1 : -1)*568);
			float angle2 =  rand7*M_PI;
			float minDist = 0.f;
			float randDist = 6000.f;
			float i = v_TexCoord.x / offset;
			
			mat3 rotation = mat3(cos(angle2),0,-sin(angle2), 0,1,0, sin(angle2),0,cos(angle2));
			extra.z=0.01f+rand4*0.09f;
			extra.z *=1;
			extra.y= (extra.z-0.01f)/0.010f;
			vec3 center = v_emitter_pos.xyz;//+(v_TexCoord.x < middle ? 1.f: -1.f)*vec3(dd,0,0);
			vec3 pos = vec3(-sin(angle)*(minDist+int(randDist*rand5)),cos(angle)*(minDist+int(randDist*rand5)),rand6*20);
			pos = rotation*pos;
			pos +=center;
			float speed = 400.f/(length(center-pos)*length(center-pos));
			speed *=10;
			out_Position = pos;
			out_Velocity =rotation*(vec3(speed*cos(angle),speed*sin(angle),0)*2)+vec3(-10,0,0);
		}
		out_Extra = extra.xyz;
		

	}else
	{
		int c = 0;
		vec3 _velocity = vec3(0);

		/*for(int i = 0; i < u_particleCount;i++)
		{
			float offset = i/float(u_particleCount);
			vec4 _extra = texture(texture2,vec2(offset,0));
			vec3 _position = texture(texture0,vec2(offset,0)).rgb;
			if(near3f(_position,position))
				continue;
			vec3 d = _position - position;
			float l = length(d);
			if(l < 0.5f)
				continue;
			c++;
			_velocity +=normalize(d)*_extra.z/(l*l);
		}*/
		
		//if(c > 0)
			_velocity /=400;
		velocity +=_velocity*time;
		velocity*=0;
		extra.y = clamp(length(velocity)*5,0,1.0f);
		//extra.y = 0.8f;
		if(extra.z > 100.f)
			extra.y=0.7f;
		out_Extra =  extra.xyz;
		out_Velocity = velocity;
		out_Position = position + velocity*time;
	}
}
#endif