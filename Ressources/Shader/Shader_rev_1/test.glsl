-- Vertex
#version 400
in vec3 in_Vertex;
out vec3 vPosition;

void main()
{
    vPosition = in_Vertex;
}

-- TessControl

#version 400
layout(vertices = 3) out;
in vec3 vPosition[];
out vec3 tcPosition[];
uniform float TessLevelInner;
uniform float TessLevelOuter;

#define ID gl_InvocationID

void main()
{
    tcPosition[ID] = vPosition[ID];
    if (ID == 0) {
        gl_TessLevelInner[0] = TessLevelInner;
        gl_TessLevelOuter[0] = TessLevelOuter;
        gl_TessLevelOuter[1] = TessLevelOuter;
        gl_TessLevelOuter[2] = TessLevelOuter;
    }
}

-- TessEval
#version 400
layout(triangles, equal_spacing, ccw) in;
in vec3 tcPosition[];
out vec3 tePosition;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    vec3 p0 = gl_TessCoord.x * tcPosition[0];
    vec3 p1 = gl_TessCoord.y * tcPosition[1];
    vec3 p2 = gl_TessCoord.z * tcPosition[2];
    tePosition = p0 + p1 + p2;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(tePosition, 1);
}

-- Geometry
#version 400
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in vec3 tePosition[3];

void main()
{
	mat3 normalMatrix = mat3(modelMatrix);
    
    gl_Position = gl_in[0].gl_Position; EmitVertex();

    gl_Position = gl_in[1].gl_Position; EmitVertex();

    gl_Position = gl_in[2].gl_Position; EmitVertex();

    EndPrimitive();
}

-- Fragment
#version 400
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0);
}