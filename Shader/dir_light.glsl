#version 330
#include "global_uniform.glsl"
/*#include "global_light_uniform.glsl"*/
#ifdef _VERTEX_

in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Tangent;

out vec3 v_Normal;

void main()
{
    v_Normal = mat3(u_matModel)*in_Normal;
    vec4 pos = u_matProjection*u_matView*u_matModel*vec4(in_Vertex,1.0f);
    gl_Position = pos; 

}

#endif

#ifdef _FRAGMENT_

uniform vec3 light_dir = vec3(0);

in vec3 v_Normal;

out vec4 out_Color;

void main (void)
{
    out_Color = vec4(1.0);
    float lambertTerm = dot(v_Normal,light_dir);
    out_Color = vec4(out_Color.xyz*(lambertTerm),out_Color.w);
}

#endif