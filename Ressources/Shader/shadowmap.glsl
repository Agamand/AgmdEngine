#version 330
#include "global_uniform.glsl"
#ifdef _VERTEX_
// Input vertex data, different for all executions of this shader.
in vec3 in_Vertex;

// Values that stay constant for the whole mesh.
uniform mat4 depthMVP;

out vec3 v_position;
void main(){
    v_position = (u_matModel *vec4(in_Vertex,1)).xyz;
    gl_Position =  depthMVP * u_matModel *vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_
// Ouput data
layout(location = 0) out vec4 out_Color;

in vec3 v_position;

void main(){

    out_Color = vec4(v_position,1.0f);
}
#endif