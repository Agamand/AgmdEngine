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
#ifdef _VERTEX_

uniform vec2 u_pixelSize;
uniform sampler2D texture0;
uniform int u_blurSize = 4;
uniform float u_brightness;

in vec2 v_TexCoord;
out vec4 out_color;

void main()
{
	float result;
	vec2 pos = v_TexCoord;

	vec2 hlim = vec2(float(-u_blurSize * 0.5 + 0.5));
	//hlim = hlim * 0.5 + 0.5;

	
	for(int i = 0; i < u_blurSize; ++i) {
		for(int j = 0; j < u_blurSize; ++j) {
			vec2 offset = (hlim + vec2(i, j)) * u_pixelSize;
			result += texture2D(u_texture, v_TexCoord + offset).r;
		}
	}
	
	result /= (u_blurSize * u_blurSize);

	out_color = vec4(vec3(result + u_brightness), 1.0);
}
#endif