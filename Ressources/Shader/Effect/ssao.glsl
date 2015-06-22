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

const int MAX_KERNEL_SIZE = 128;
uniform vec3 u_kernel[MAX_KERNEL_SIZE];
uniform int u_kernelSize;
uniform float u_radius;
uniform float u_ssaoPower;
uniform mat4 u_matProjection;
uniform mat4 u_matProjectionInv;
uniform sampler2D texture0; // depth
uniform sampler2D texture1; //normal
uniform sampler2D texture2; // noise

in vec2 v_TexCoord;
out vec4 out_color;

//z change of basis from ndc to view space
float linearizeDepth(in float depth, in mat4 projMatrix) {
	return projMatrix[3][2] / (depth * projMatrix[2][3] + projMatrix[3][3]);
}

float ssao(in mat3 kernelBasis, in vec3 origin) {
	float occlusion = 0.0;

	for(int i = 0; i < u_kernelSize; ++i) {
		//get sample position
		vec3 sample = kernelBasis * u_kernel[i];
		sample = sample * u_radius + origin;

		//project sample position
		vec4 offset = vec4(sample, 1.0);
		offset = u_matProjection * offset;
		offset.xy /= offset.w;
		offset.xy = offset.xy * 0.5 + 0.5;
		
		//get sample depth
		float sampleDepth = texture2D(texture0, offset.xy).z;
		sampleDepth = linearizeDepth(sampleDepth, u_matProjectionInv);
		
		//range check and accumulate
		float rangeCheck = smoothstep(0.0, 1.0, u_radius / abs(origin.z - sampleDepth));
		occlusion += rangeCheck * (1.0 - step(sampleDepth, sample.z));
	}

	occlusion = 1.0 - (occlusion / float(u_kernelSize));
	return pow(occlusion, u_ssaoPower);
}

void main() {
	float depth = texture2D(texture0, v_TexCoord).x;
	
	if(depth == 1.0) {
		out_color = vec4(1.0);
		return;
	}

	vec3 normal = texture2D(texture1, v_TexCoord).xyz - 0.5;
	normal = normalize(normal);

	vec3 windowSpacePosition = vec3(v_TexCoord * 2.0 - 1.0, depth);

	vec4 origin = u_matProjectionInv * vec4(windowSpacePosition, 1.0);
	origin /= origin.w;
	
	//construct change of basis matrix btn
	vec3 rvec = texture2D(texture2, gl_FragCoord.xy / 4.0).xyz * 2.0 - 1.0;
	vec3 tangent = normalize(rvec - normal * dot(rvec, normal));
	vec3 bitangent = cross(tangent, normal);
	mat3 tbn = mat3(tangent, bitangent, normal);

	float occlusion = ssao(tbn, origin.xyz);

	out_color = vec4(vec3(occlusion), 1.0);
}
#endif
