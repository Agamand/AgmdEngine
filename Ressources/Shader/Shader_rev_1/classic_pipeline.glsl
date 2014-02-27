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

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform int RenderFlags;
uniform float du = 20.0f;
uniform sampler2D texture5;

vec3 _lightDir = vec3(1.0,1.0,1.0);

uniform vec3 light;




void main()
{
	vec3 vertex = in_Vertex;

	
	color = in_Color;
	texCoord0 = in_TexCoord0;
	normal = normalMatrix*in_Normal;
	lightDir = light;
	tangent = normalMatrix * in_Tangent.xyz;
	binormal = cross(normal, tangent) * in_Tangent.w;
	vec4 pos = viewMatrix * modelMatrix * vec4(in_Vertex, 1.0f);
	eye = -(pos.xyz / pos.w);
	if((RenderFlags & 64) != 0)
	{
		vec4 dv = texture2D( texture5, texCoord0);
		float df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
		vertex = vertex + in_Normal * df * du; 
	}
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex,1.0f);
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

layout(location = 0) out vec4 out_Color;
uniform sampler2D texture0;
uniform int RenderFlags;
uniform sampler2D texture4;
uniform sampler2D texture5;

void directLight()
{
	mat3 mtangent = mat3(tangent.x , binormal.x , normal.x,
						 tangent.y, binormal.y, normal.y,
						 tangent.z  , binormal.z  , normal.z);
	mat3 inv_mtangent = inverse(mtangent);
						 
	vec3 _eye = eye;
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	if((RenderFlags & 32 ) != 0)
	{
		//L = mtangent*L;
		normalize(L);
		N = normalize( texture2D(texture4, texCoord0).xyz * 2.0 - 1.0);
		N = inv_mtangent*N;
		N = normalize(N);
	}
	
	float lambertTerm = dot(N,L);
	//out_Color = vec4(N,1.0);
	if(lambertTerm > 0 && lambertTerm <= 1)
		out_Color = vec4(out_Color.xyz*(lambertTerm),out_Color.w);
	else out_Color = vec4(out_Color.xyz*0.0,out_Color.w);
}

void main()
{
	out_Color = vec4(1.0);
	if((RenderFlags & 2 ) != 0)
		out_Color = texture2D(texture0, texCoord0);
		
	//if((RenderFlags & 64 ) != 0)
		//out_Color = texture2D(texture5, texCoord0);
	//directLight();
	//out_Color = vec4(1.0f);
}