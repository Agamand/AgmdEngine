#include "ParticlesEmitter.h"
#include <Core/Tools/Fast2DSurface.h>
#include <Core/MediaManager.h>
#include <random>
#define MAX_PER_BUFFER 16384

void ParticlesEmitter::Update(a_uint32 time)
{
    Driver& driver = Driver::Get();

    std::swap(position_buffer[0], position_buffer[1]);
    std::swap(velocity_buffer[0], velocity_buffer[1]);
    std::swap(extra_buffer[0], extra_buffer[1]);
    m_fbo->SetTexture(position_buffer[0], 0);
    m_fbo->SetTexture(velocity_buffer[0], 1);
    m_fbo->SetTexture(extra_buffer[0], 2);
    m_fbo->Clear();
    a_uint32 buffer[3];
    a_uint32 flags[3] = {COLOR_ATTACHMENT, COLOR_ATTACHMENT + 1, COLOR_ATTACHMENT + 2};
    m_fbo->GenerateBufferFlags(buffer, 3, flags);
    m_fbo->DrawBuffers(3, buffer);
    m_fbo->Bind();
    driver.SetViewPort(ivec2(), position_buffer[1].GetSize());
    driver.SetCurrentProgram(m_program.GetShaderProgram());
    driver.SetCurrentTransform(m_transform);
    m_program.SetParameter("u_time_diff", (float)time);
    m_program.SetParameter("u_matProjectionPlane", ortho<float>(0, 1, 0, 1));
    m_program.SetParameter("u_particleCount", draw_count > 1 ? MAX_PER_BUFFER : m_particleCount);
    m_program.SetParameter("u_colorIndex", color);
    int i = rand();
    m_program.SetParameter("u_seed", i);
    driver.SetTexture(0, position_buffer[1].GetTexture());
    driver.SetTexture(1, velocity_buffer[1].GetTexture());
    driver.SetTexture(2, extra_buffer[1].GetTexture());
    Fast2DSurface::Instance().Draw();
    driver.SetCurrentProgram(NULL);
    m_fbo->UnBind();
}

void ParticlesEmitter::Draw() const
{
    Driver& driver = Driver::Get();

    float ar = driver.GetAspectRatio();
    //Texture::TextureRender(velocity_buffer[0]);
    driver.SetViewPort(ivec2(), driver.GetScreen());
    driver.Enable(RENDER_POINTSIZE_SHADER, true);
    driver.Enable(RENDER_POINTSPRITE, true);
    //driver.Enable(RENDER_ZTEST,true);
    driver.SetupDepthTest(DEPTH_LEQUAL);
    driver.Enable(RENDER_ZWRITE, true);
    driver.SetDeclaration(m_declaration);

    driver.SetIndexBuffer(m_index);
    driver.SetCurrentProgram(m_diffuse.GetShaderProgram());
    float offset = 60 * 5 * 4;
    m_diffuse.SetParameter("u_matProjectionPlane", ortho<float>(-offset * ar, offset * ar, -offset, offset));
    m_diffuse.SetParameter("u_particleCount", draw_count > 1 ? MAX_PER_BUFFER : m_particleCount);
    driver.SetTexture(0, position_buffer[1].GetTexture());
    driver.SetTexture(1, extra_buffer[1].GetTexture());
    driver.SetTexture(2, m_diffuse_texture.GetTexture());
    driver.SetVertexBuffer(0, m_particles);
    driver.Enable(RENDER_ALPHABLEND, true);
    driver.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_INVSRCALPHA);
    for (int i = 0; i < draw_count; i++)
    {
        m_diffuse.SetParameter("u_yoffset", i * 1.0f / draw_count);
        driver.DrawIndexedPrimitives(PT_POINTLIST, 0, i == draw_count - 1 && m_particleCount % MAX_PER_BUFFER > 0 ? m_particleCount % MAX_PER_BUFFER : m_particles.GetCount());
    }
    driver.SetCurrentProgram(NULL);
    driver.Enable(RENDER_POINTSIZE_SHADER, false);
    driver.Enable(RENDER_POINTSPRITE, false);
    driver.Enable(RENDER_ALPHABLEND, false);
}

void ParticlesEmitter::Draw(const BaseShaderProgram* program) const
{
    Driver& driver = Driver::Get();

    float ar = driver.GetAspectRatio();
    //Texture::TextureRender(velocity_buffer[0]);
    driver.SetViewPort(ivec2(), driver.GetScreen());
    driver.Enable(RENDER_POINTSIZE_SHADER, true);
    driver.Enable(RENDER_POINTSPRITE, true);
    driver.SetDeclaration(m_declaration);

    driver.SetIndexBuffer(m_index);
    driver.SetCurrentProgram(program);
    float offset = 60 * 5 * 4;
    m_diffuse.SetParameter("u_matProjectionPlane", ortho<float>(-offset * ar, offset * ar, -offset, offset));
    m_diffuse.SetParameter("u_particleCount", draw_count > 1 ? MAX_PER_BUFFER : m_particleCount);
    driver.SetTexture(0, position_buffer[1].GetTexture());
    driver.SetTexture(1, extra_buffer[1].GetTexture());
    driver.SetTexture(2, m_diffuse_texture.GetTexture());
    driver.SetVertexBuffer(0, m_particles);
    driver.Enable(RENDER_ALPHABLEND, true);
    driver.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_INVSRCALPHA);
    for (int i = 0; i < draw_count; i++)
    {
        m_diffuse.SetParameter("u_yoffset", i * 1.0f / draw_count);
        driver.DrawIndexedPrimitives(PT_POINTLIST, 0, i == draw_count - 1 && m_particleCount % MAX_PER_BUFFER > 0 ? m_particleCount % MAX_PER_BUFFER : m_particles.GetCount());
    }
    driver.SetCurrentProgram(NULL);
    driver.Enable(RENDER_POINTSIZE_SHADER, false);
    driver.Enable(RENDER_POINTSPRITE, false);
    driver.Enable(RENDER_ALPHABLEND, false);
}

ParticlesEmitter::ParticlesEmitter(ShaderProgram& program, int particlesCount /*= 250*/, Transform* tr /* = NULL*/) : m_program(program)
{
    m_transform = tr ? tr : new Transform();
    Init(particlesCount);
}

ParticlesEmitter::ParticlesEmitter(std::string& shaderpath, int particlesCount /*= 250*/, Transform* tr /* = NULL*/)
{
    m_transform = tr ? tr : new Transform();
    m_program.LoadFromFile(shaderpath);
    Init(particlesCount);
}

void ParticlesEmitter::Init(int particlesCount)
{
    m_diffuse.LoadFromFile("Shader/particle_render.glsl");
    m_diffuse_texture.CreateFromFile("Texture/SunYello.bmp", PXF_A8R8G8B8);
    TDeclarationElement Elements[] =
    {
        {0, ELT_USAGE_POSITION, ELT_TYPE_FLOAT1}
    };
    Driver& driver = Driver::Get();
    m_declaration = driver.CreateVertexDeclaration(Elements);


    float* buffer = new float[particlesCount];

    draw_count = particlesCount / MAX_PER_BUFFER + (particlesCount % MAX_PER_BUFFER > 0 ? 1 : 0);
    m_particleCount = draw_count > 1 ? MAX_PER_BUFFER : particlesCount;
    for (int i = 0; i < 2; i++)
        position_buffer[i].Create(ivec2(m_particleCount, draw_count), PXF_R32G32B32, TEXTURE_2D);
    for (int i = 0; i < 2; i++)
        velocity_buffer[i].Create(ivec2(m_particleCount, draw_count), PXF_R32G32B32, TEXTURE_2D);
    for (int i = 0; i < 2; i++)
        extra_buffer[i].Create(ivec2(m_particleCount, draw_count), PXF_R16G16B16, TEXTURE_2D);
    for (int i = 0; i < m_particleCount; i++)
        buffer[i] = i;
    a_uint16* ibuffer = new a_uint16[m_particleCount];
    int indexcount = m_particleCount;
    for (int i = 0; i < indexcount; i++)
        ibuffer[i] = i;
    m_particles = driver.CreateVertexBuffer(m_particleCount, 0, buffer);
    m_index = driver.CreateIndexBuffer(indexcount, 0, ibuffer);
    m_fbo = driver.CreateFrameBuffer();
    m_particleCount = particlesCount;
    //velocity_buffer[0].CreateFromFile("Texture/roadV3.png",PXF_A8R8G8B8);
    color = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    delete[] buffer;
    delete[] ibuffer;
}

ParticlesEmitter::~ParticlesEmitter()
{
    delete m_fbo;
}
