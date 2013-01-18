-- Vertex
#version 400

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_TexCoord0;

struct vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord0;
};

out vertex vVertex;

void main()
{
    vVertex.Position = in_Vertex;
	vVertex.Normal = in_Normal;
	vVertex.TexCoord0 = in_TexCoord0;
}

-- TessControl
#version 400
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

-- TessEval
#version 400
layout(triangles, equal_spacing, cw) in;

struct vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord0;
};

struct vertex2
{
	vec3 Normal;
	vec2 TexCoord0;
};

in vertex tcVertex[];
out vertex2 teVertex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform float du = 20.0f;

uniform int RenderFlags;
uniform sampler2D texture4, texture5;

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
	
	if((RenderFlags & 64) != 0)
	{
		vec4 dv = texture(texture5, _texcoord0);
		float df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
		_pos = _pos + _normal * df * du; 
	}
	
	teVertex.Normal = _normal;
	teVertex.TexCoord0 = _texcoord0;
	
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(_pos, 1);
}

-- Geometry
#version 400
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

struct vertex
{
	vec3 Normal;
	vec2 TexCoord0;
};

in vertex teVertex[];

out vec3 fgTex;
out vec3 fgNormal;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = gl_in[i].gl_Position;
		fgTex = vec3(teVertex[i].TexCoord0,0.0);
		fgNormal = vec3(teVertex[i].teNormal,0.0);
		
		
		EmitVertex();
	}

    EndPrimitive();
}

-- Fragment
#version 400

uniform int RenderFlags;
uniform sampler2D texture0;


in vec3 fgTex;
in vec3 fgNormal;

out vec4 out_Color;

void main()
{
	out_Color = vec4(1.0);
	//ATTENTION DEPASSEMENT DANS LA MATRICE DE PROJECTION
	vec2 d = fgNormal;
	if((RenderFlags & 2 ) != 0)
		out_Color = vec4(texture(texture0, fgTex.xy).rgb,1.0f);
}