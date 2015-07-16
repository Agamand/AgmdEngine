#version 330
#ifdef _VERTEX_

uniform mat4 u_matProjection;

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = in_TexCoord0;
	gl_Position = u_matProjection*vec4(in_Vertex,1.0f);
}

#endif

#ifdef _FRAGMENT_
uniform sampler2D texture0;
uniform sampler2D texture1;
in vec2 v_TexCoord;
out vec4 out_Color;

uniform float u_time;


void main ()
{
	ivec2 size = textureSize(texture1,0);
	
	float _char = floor(u_time*32)/32;
		
	out_Color = texture(texture0,v_TexCoord)*texture(texture1,(v_TexCoord + vec2(1,1)*_char)*4).r;
}


#endif