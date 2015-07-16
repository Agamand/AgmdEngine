#version 330

uniform vec2 u_pixelSize;
uniform sampler2D u_texture;
uniform int u_blurSize = 4;
uniform float u_brightness;

in vec2 v_uv;
out vec4 o_color;

void main()
{
	float result;
	vec2 pos = v_uv;

	vec2 hlim = vec2(float(-u_blurSize * 0.5 + 0.5));
	//hlim = hlim * 0.5 + 0.5;

	
	for(int i = 0; i < u_blurSize; ++i) {
		for(int j = 0; j < u_blurSize; ++j) {
			vec2 offset = (hlim + vec2(i, j)) * u_pixelSize;
			result += texture2D(u_texture, v_uv + offset).r;
		}
	}
	
	result /= (u_blurSize * u_blurSize);

	o_color = vec4(vec3(result + u_brightness), 1.0);
}