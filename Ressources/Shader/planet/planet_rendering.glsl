#version 420

#include <common/global_uniform.glsl>
//#define TESSELATE

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;

#ifdef TESSELATE
struct vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord0;
};

out vertex vVertex;
#else
out vec2 v_texCoord0;
out vec3 v_normal;
out vec3 v_position;
#endif


uniform samplerCube texture0;
uniform float u_offset = 0.05f;
float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

void main()
{
	vec3 vertex = in_Vertex;
	vec4 position; 
	vec3 normal;
	position.w = 1.0f;
	float scale = 1.f;
	
	position.xyz = normalize( normal = ( u_matModel * vec4(in_Vertex,1)).xyz);
	position.xyz *= scale;
	float displacement = rgb2grayscale(texture(texture0,position.xyz).rgb);
	//position = vec4(normal*scale,1);
	if(in_TexCoord0.x < 0.0f || in_TexCoord0.y < 0.0f || in_TexCoord0.x > 1.0f || in_TexCoord0.y > 1.0f)
	{
		displacement =-1.0f;
		position += vec4(scale*normal*displacement,0);
	}
	else{
		displacement = clamp(displacement,0.0f,1.f);
		position += vec4(scale*normal*displacement*u_offset,0);
	}
		

	
	vec4 comp_position = u_matViewProjection * position;

	#ifdef TESSELATE
		vVertex.Position = position.xyz;
		vVertex.Normal = normal;
		vVertex.TexCoord0 = in_TexCoord0;
	#else
		v_position = position.xyz;
		v_normal = normal;
		v_texCoord0 = in_TexCoord0;
	#endif
	gl_Position = comp_position;
}

#endif
#ifdef TESSELATE
#ifdef _TESS_CONTROL8_
#extension GL_ARB_tessellation_shader : enable
layout(vertices = 3) out;

struct vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord0;
};

in vertex vVertex[];
out vertex tcVertex[];

uniform float TessLevelInner;
uniform float TessLevelOuter;

#define ID gl_InvocationID

void main()
{
    tcVertex[ID] = vVertex[ID];
	
    if (ID == 0) {
        gl_TessLevelInner[0] = TessLevelInner;
        gl_TessLevelOuter[0] = TessLevelOuter;
        gl_TessLevelOuter[1] = TessLevelOuter;
        gl_TessLevelOuter[2] = TessLevelOuter;
    }
}

#endif

#ifdef _TESS_EVALUATION8_
#extension GL_ARB_tessellation_shader : enable
layout(triangles, equal_spacing, cw) in;

struct vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord0;
};

struct vertex2
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord0;
};

in vertex tcVertex[];
out vertex2 teVertex;

void main()
{
	vec3 _pos = vec3(0.0);
	vec3 _normal = vec3(0.0);
	vec2 _texcoord0 = vec2(0.0);
	for(int i = 0; i < 3; i++)
	{
		_pos += gl_TessCoord[i]*tcVertex[i].Position;
		_normal += gl_TessCoord[i]*tcVertex[i].Normal;
		_texcoord0 += gl_TessCoord[i]*tcVertex[i].TexCoord0;
	}
	
	
	teVertex.Normal = _normal;
	teVertex.TexCoord0 = _texcoord0;
	teVertex.Position = _pos;
		
    gl_Position = u_matViewProjection *  vec4(_pos, 1);
}
#endif

#ifdef _GEOMETRY8_

layout(triangles,invocations = 1 ) in;
layout(triangle_strip, max_vertices = 3) out;

struct vertex
{
	vec3 Position;	 
	vec3 Normal;
	vec2 TexCoord0;
};

in vertex teVertex[];
out vec2 v_texCoord0;
out vec3 v_position;
out vec3 v_normal;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{


		EmitVertex();
	}

    EndPrimitive();
}

vec3 calcNormal(vec3 v0, vec3 v1, vec3 v2)
{
    vec3 edge0 = v1 - v0;
    vec3 edge1 = v2 - v0;
    return normalize(cross(edge1, edge0));
}

void main()
{
    //Out.normal = calcNormal(In[0].vertex, In[1].vertex, In[2].vertex);
    //Out.normalEye = vec3(ModelView * vec4(Out.normal, 0.0));

	for(int i = 0; i < gl_in.length(); ++i)
	{
		v_position = teVertex[i].Position;
		v_normal = teVertex[i].Normal;
		v_texCoord0 = teVertex[i].TexCoord0;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
#endif
#endif
#ifdef _FRAGMENT_

in vec2 v_texCoord0;
in vec3 v_normal;
in vec3 v_position;

layout(location = 0) out vec4 out_Color;
uniform samplerCube texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform float u_divisor = 1;
float texMult = 30f;
float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

vec3 normal2color(vec3 normal)
{
	return normal/2+vec3(0.5);
}

void main()
{
	vec3 color;
	float offset = rgb2grayscale(color = texture(texture0,v_position.xyz).rgb);
	
	if(offset < 0.3)
		color = texture(texture2,v_texCoord0*texMult/u_divisor).rgb;
	else if(offset > 0.8f)
		color = texture(texture3,v_texCoord0*texMult/u_divisor).rgb;
	else color = texture(texture2,v_texCoord0*texMult/u_divisor).rgb*(0.6-offset+0.3)/0.6+texture(texture3,v_texCoord0*texMult/u_divisor).rgb*(offset-0.3)/0.6;
	color = texture(texture1,vec2(offset,0)).rgb;
	//out_Color =vec4(1);
	out_Color = vec4(color,1.0f);
}
#endif