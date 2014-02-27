ShaderPipeline normalMapping 
{
	Properties
	{
		RenderType Opaque
		Use TangentSpace
		Use TexCoord(0)
	}
	UniformInput 
	{
		diffuseTex(Texture2D) = "white"
		normalmapTex(Texture2D) = "blue"
	}
	
	SubRoutine Diffuse
	{
		GLSLBEGIN
		vec4 diffuse()
		{
			return texture(diffuseTex, v_TexCoord0);
		}
		GLSLEND
	}
	
	SubRoutine Normal
	{
		GLSLBEGIN
		vec3 normal()
		{
			vec3 N = texture(normalmapTex, v_TexCoord0);
			return vec3(clamp(0.5 + 0.5*N.x,0.0,1.0),clamp(0.5 + 0.5*N.y,0.0,1.0),clamp(0.5 + 0.5*N.z,0.0,1.0));
		}
		GLSLEND
	}

}