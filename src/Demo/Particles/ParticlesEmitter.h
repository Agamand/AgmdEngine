#ifndef _PARTICLESEMITTER_H_
#define _PARTICLESEMITTER_H_

#include <Core/Renderer.h>
#include <Core/Buffer/Buffer.h>
#include <Transform.h>
#include <Core/Declaration.h>
#include <Core/Shader/ShaderProgram.h>
#include <Core/Texture/Texture.h>
#include <Core/Buffer/FrameBuffer.h>

using namespace  Agmd;
class ParticlesEmitter
{
public:
	ParticlesEmitter(std::string &shaderpath, int particlesCount = 250, Transform* tr = NULL);
	ParticlesEmitter(ShaderProgram& program, int particlesCount = 250, Transform* tr = NULL);
	
	void Draw() const;
	void Update(a_uint32 time);
	Texture position_buffer[2];
	Texture velocity_buffer[2];
	Texture extra_buffer[2]; //life and other stuff

	Transform* GetTransform(){return m_transform;}
private:
	
	void Init(int particlesCount);
	Texture m_diffuse_texture;
	Buffer<float> m_particles; // contains id of particles
	Buffer<a_uint16> m_index;
	DeclarationPtr  m_declaration;
	ShaderProgram   m_program;
	ShaderProgram   m_diffuse;
	//Texture position_buffer[2];
	//Texture velocity_buffer[2];
	//Texture extra_buffer[2]; //life and other stuff
	FrameBuffer* m_fbo;
	int m_particleCount;
	int draw_count;

	/*need to be in sceneNode*/
	Transform* m_transform;
	
};

#endif