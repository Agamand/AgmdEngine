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

uniform float seed;
in vec2 v_TexCoord;
out vec4 out_Color;

float RND_1d(vec2 x)
{
    //uint n = floatBitsToUint(x.y * 214013.0 + x.x * 2531011.0);
    uint n = floatBitsToUint(x.y * seed + x.x * seed);
    n = n * (n * n * 15731u + 789221u);
    n = (n >> 9u) | 0x3F800000u;

    return 2.0 - uintBitsToFloat(n);
}

vec4 randomColor(vec2 coord)
{
    return vec4(RND_1d(vec2(coord.x, 0)),RND_1d(vec2(0, coord.y)),RND_1d(coord),1.0);
}

void main (void)
{
    vec2 center = vec2(0.5);
    vec2 texcoord = center - v_TexCoord;
    float rand = (int(seed)%1024)/1024.0*50.0;
    out_Color = vec4(vec3(1.0+cos(length(texcoord)*3.14*2+ 3.14*rand),1.0+cos(length(texcoord)*3.14*2+3.14*1/3+ 3.14*rand),1.0+cos(length(texcoord)*3.14*2+3.14*2/3+ 3.14*rand))*0.5,1.0);
}
#endif