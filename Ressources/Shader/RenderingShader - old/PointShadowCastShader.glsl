#version 330
#ifdef _VERTEX_
#include "global_uniform.glsl"
in vec3 in_Vertex;


uniform mat4 depthMVP;

out vec3 v_Vertex;
void main(){
	v_Vertex = (u_matModel *vec4(in_Vertex,1)).xyz;
}
#endif

#ifdef _GEOMETRY_


layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 v_Vertex[];

uniform mat4 depthP;


vec4 layer_select(vec3 vertex, int layer)
{
	if(layer == 1)
		return vec4(-vertex.x,vertex.yz,1.0f);
	else if(layer == 2)
		return vec4(vertex.y,vertex.x,vertex.z,1.0f);
	else if(layer == 3)
		return vec4(-vertex.y,vertex.x,vertex.z,1.0f);
	else if(layer == 4)
		return vec4(vertex.z,vertex.y,vertex.x,1.0f);
	else if(layer == 5)
		return vec4(-vertex.z,vertex.y,vertex.x,1.0f);

	return vec4(vertex,1.0f);
}



void main() {
    int i, layer;
    for (layer = 0; layer < 6; layer++) {
        gl_Layer = layer;
        for (i = 0; i < 3; i++) {
            gl_Position = depthP*layer_select(v_Vertex[i],layer);
            EmitVertex();
        }
        EndPrimitive();
    }
}
#endif


#ifdef _FRAGMENT_
// Ouput data
layout(location = 0) out vec3 out_Color;

in vec3 v_position;

void main(){

	out_Color = vec3(gl_FragCoord.z);
}
#endif
