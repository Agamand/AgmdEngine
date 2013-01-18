-- Vertex
#version 330

in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;
in vec4 in_Tangent;

out vec3 tangent;
out vec3 binormal;

out vec4 color;
out vec2 texCoord0;
out vec3 normal;
out vec3 lightDir;
out vec3 eye;
out VertexNormal
{
	vec3 normal;
	vec3 pos;
	vec3 tangent;
	vec3 binormal;
} VertexN;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform int RenderFlags;
uniform sampler2D texture5;
uniform sampler2D texture4;


vec3 _lightDir = vec3(1.0,1.0,1.0);

void main()
{
	vec3 vertex = in_Vertex;

	
	color = in_Color;
	texCoord0 = in_TexCoord0;
	normal = normalMatrix*in_Normal;
	lightDir = _lightDir;
	tangent = normalMatrix * in_Tangent.xyz;
	binormal = cross(normal, tangent) * in_Tangent.w;

	if((RenderFlags & 64 ) != 0)
	{
		vec4 dv = texture2D( texture5, texCoord0);
		float df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
		float du = 2.0f;
		vertex = vertex + in_Normal * df * du; 
	}
	mat3 mtangent = mat3(tangent.x , binormal.x , normal.x,
						 tangent.y, binormal.y, normal.y,
						 tangent.z  , binormal.z  , normal.z);
						 
	if((RenderFlags & 32 ) != 0 && false)
	{
		mat3 invmtangent = inverse(mtangent);
		vec3 N = normalize( texture2D(texture4, texCoord0).xyz * 2.0 - 1.0);
		normal = invmtangent*N;
	}
	
	
	vec4 pos = viewMatrix * modelMatrix * vec4(vertex, 1.0f);
	eye = -(pos.xyz / pos.w);
	VertexN.normal = normalize(mat3(viewMatrix)*normal);
	VertexN.pos = pos.xyz;
	VertexN.tangent = normalize(mat3(viewMatrix)*tangent);
	VertexN.binormal = normalize(mat3(viewMatrix)*binormal);
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex,1.0f);
}

-- Geometry
#version 330
#extension GL_geometry_shader4 : enable
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec4 color;

in VertexNormal
{
	vec3 normal;
	vec3 pos;
	vec3 tangent;
	vec3 binormal;
} VertexNormal[];


void drawLine( vec4 _color, vec3 from, vec3 to )
{
    color = _color;
	gl_Position = projectionMatrix * vec4( from, 1.0 );
	EmitVertex();

	color = _color;
	gl_Position = projectionMatrix * vec4( to, 1.0 );
	EmitVertex();

	EndPrimitive();
}

void main( void )
{
	for( int i = 0 ; i < gl_VerticesIn ; i++ )
	{
		drawLine(vec4(1,0,0,1),VertexNormal[i].pos, VertexNormal[i].pos + VertexNormal[i].normal);
		//drawLine(vec4(0,1,0,1),VertexNormal[i].pos, VertexNormal[i].pos + VertexNormal[i].tangent);
		//drawLine(vec4(0,0,1,1),VertexNormal[i].pos, VertexNormal[i].pos + VertexNormal[i].binormal);
	}
	EndPrimitive ();
}

-- Fragment
#version 330

in vec3 tangent;
in vec3 binormal;

in vec4 color;
in vec2 texCoord0;
in vec3 normal;
in vec3 lightDir;
in vec3 eye;

out vec4 out_Color;

void main()
{
	out_Color = color;
}

