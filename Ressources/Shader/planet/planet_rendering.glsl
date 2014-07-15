#version 420

#include <common/global_uniform.glsl>

#include <Core/noise/perlin.glsl>
float getDisplacement(vec3 normal)
{
	float noise = 10.0f *  -.10 * turbulence( .5 * normal );
    float b = 5.0 * pnoise( 0.05 * normal, vec3( 100.0 ) );

	return 10. * noise + b;
}
const float const_scalling = 2.0f;
#ifdef _VERTEX_
in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;

#include <common/math.glsl>

out vec3 v_normal;
out vec3 v_position;
out vec2 v_texCoord0;
out float v_displacement;

uniform sampler2D texture0;
uniform float u_offset = 0.05f;
uniform mat4 u_position_matrix;

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
	float scale = 1f;
	
	position.xyz = normal = (( u_position_matrix * vec4(in_Vertex,1)).xyz);
	position.xyz *= scale;

	float displacement = v_displacement =  texture(texture0,clamp(in_TexCoord0,0,1)).x;
	//position = vec4(normal*scale,1);
	if(in_TexCoord0.x < 0.0f || in_TexCoord0.y < 0.0f || in_TexCoord0.x > 1.0f || in_TexCoord0.y > 1.0f)
	{
		displacement =displacement*u_offset*const_scalling-0.1f;
		//position = vec4(0,0,0,1);
		//position += vec4(scale*normal*displacement,0);
	}
	else{
		displacement = clamp(displacement,0.0f,1.f)*u_offset*const_scalling;
		//position += vec4(scale*normal*displacement,0);
	}


	
	vec4 comp_position = u_matViewProjection *u_matModel* position;

	v_position = position.xyz;
	v_normal = normal;
	v_texCoord0 = clamp(in_TexCoord0,0,1);

	gl_Position = comp_position;
}

#endif

#ifdef _FRAGMENT_

#include <common/math.glsl>

in vec3 v_normal;
in vec3 v_position;
in vec2 v_texCoord0;
in float v_displacement;

layout(location = 0) out vec4 out_Color;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float u_divisor = 1;
uniform float u_offset = 0.05f;

float texMult = 30f;

float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

vec3 normal2color(vec3 normal)
{
	return normal/2+vec3(0.5);
}

vec3 color2normal(vec3 color)
{
	return (color-vec3(0.5))*2;
}
const vec3 off = vec3(-1,0,1)*0.1f;
const ivec3 _off = ivec3(-1,0,1);

vec3 getNormal(vec2 angles)
{
	
	vec4 displacementTable = texture(texture2,v_texCoord0);//texelFetch(texture2,ivec2(v_texCoord0.x*1024,v_texCoord0.x*1024));

    vec3 vx1 = sphere2Cart(angles+off.xy);
    vec3 vx2 = sphere2Cart(angles+off.zy);

    vec3 vy1 = sphere2Cart(angles+off.yx);
    vec3 vy2 = sphere2Cart(angles+off.yz);

    vx1 *=1+displacementTable.r*u_offset*const_scalling;
    vx2 *=1+displacementTable.g*u_offset*const_scalling;
    
    vy1 *=1+displacementTable.b*u_offset*const_scalling;
    vy2 *=1+displacementTable.a*u_offset*const_scalling;

    vec3 va = normalize(vx2-vx1);
    vec3 vb = normalize(vy1-vy2);
    return cross(va,vb);
}



float getDisplacementFor(vec2 angles, vec2 offset)
{
	vec3 vx1 = sphere2Cart(angles+offset);
	return getDisplacement(vx1);
}

vec3 _getNormal(vec2 angles)
{


    vec3 vx1 = sphere2Cart(angles+off.xy);
    vec3 vx2 = sphere2Cart(angles+off.zy);

    vec3 vy1 = sphere2Cart(angles+off.yx);
    vec3 vy2 = sphere2Cart(angles+off.yz);

    vx1 *=1+getDisplacement(vx1)*u_offset*const_scalling;
    vx2 *=1+getDisplacement(vx2)*u_offset*const_scalling;
 
    vy1 *=1+getDisplacement(vy1)*u_offset*const_scalling;
    vy2 *=1+getDisplacement(vy2)*u_offset*const_scalling;

    vec3 va = normalize(vx2-vx1);
    vec3 vb = normalize(vy1-vy2);
    return cross(va,vb);
}


vec3 getNormalv3(vec2 angles,float displacement)
{
	
	vec4 displacementTable = texture(texture2,v_texCoord0);//texelFetch(texture2,ivec2(v_texCoord0.x*1024,v_texCoord0.x*1024));

    vec3 vx1 = sphere2Cart(angles+off.xy);
    vec3 vx2 = sphere2Cart(angles+off.zy);

    vec3 vy1 = sphere2Cart(angles+off.yx);
    vec3 vy2 = sphere2Cart(angles+off.yz);

    vx1 *=1+(displacement+(displacementTable.r-0.5f)*0.1f)*u_offset*const_scalling;
    vx2 *=1+(displacement+(displacementTable.g-0.5f)*0.1f)*u_offset*const_scalling;
    
    vy1 *=1+(displacement+(displacementTable.b-0.5f)*0.1f)*u_offset*const_scalling;
    vy2 *=1+(displacement+(displacementTable.a-0.5f)*0.1f)*u_offset*const_scalling;

    vec3 va = normalize(vx2-vx1);
    vec3 vb = normalize(vy1-vy2);
    return cross(va,vb);
}





const vec3 l = normalize(vec3(1,1,0));
void main()
{
	vec3 color;
	float offset = texture(texture0,v_texCoord0).x;//getDisplacement(v_normal); //rgb2grayscale(color = texture(texture0,v_texCoord0).rgb);
	vec2 angles = cart2sphere(v_normal);
	vec3 normal = color2normal(texture(texture2,v_texCoord0).rgb);//_getNormalV3(angles);
	//normal.z = 0;

	color = texture(texture1,vec2(clamp(offset,0,0.98f),0)).rgb;
	
	float lambert =clamp(dot(normal,l),0,1),
	lambert2 = clamp(dot(v_normal,l),0,1);
	out_Color = vec4(vec3(color*lambert),1);
	out_Color = vec4(vec3(offset),1);

	//out_Color = vec4(texture(texture0,v_texCoord0));
		//out_Color = vec4(vec3(min(lambert,lambert2)),1.0f);
	

	//out_Color = vec4(vec3(lambert*color),1.0f);
	//out_Color = vec4(vec3(displacementTable.w),1.0f);
	//out_Color = vec4(texture(texture2,v_texCoord0).rgb,1.0f);
	//out_Color = vec4(vec3(displacementTable.y-0.1*getDisplacementFor(angles,off.xy))*100,1.0f);
	//out_Color = vec4(vec3(displacementTable.x-0.1*getDisplacementFor(angles,off.zy))*100,1.0f);
	//out_Color = vec4(vec3(displacementTable.w-0.1*getDisplacementFor(angles,off.yz))*100,1.0f);
	//out_Color = vec4(vec3(displacementTable.z-0.1*getDisplacementFor(angles,off.yx))*100,1.0f);
	//out_Color = vec4(texture(texture1,v_texCoord0).rgb,1.0f);
	//out_Color = displacementTable;
	//out_Color =vec4(xdiff,0,0,1);
	//out_Color = vec4(vec3(getDiff(angles).x),1);
}
#endif