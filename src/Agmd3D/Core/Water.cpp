#include <Core/Water.h>
#include <Core/Renderer.h>
#include <Core/MediaManager.h>
#include <Core/Scene.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Shader/BaseShaderProgram.h>

#include <ctime>

#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

namespace Agmd
{

	Water::Water(ivec2 _size, ivec2 _poly) :
	Model(),
	size(_size),
	n_poly(_poly),
	scene(NULL)
	{
		m_PrimitiveType = PT_TRIANGLELIST;
		generate();
		m_program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/water.glsl");
		m_programWaterNormal = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/waterNormal.glsl");
		fbo[0] = Renderer::Get().CreateFrameBuffer();
		fbo[1] = Renderer::Get().CreateFrameBuffer();

		ivec2 size = Renderer::Get().GetScreen();
		m_CubeMap.Create(ivec2(512),PXF_A8R8G8B8,TEXTURE_CUBE);
		m_WaterNormal.Create(ivec2(512),  PXF_A8R8G8B8, TEXTURE_2D,TEX_NOMIPMAP);

		m_Depth = Renderer::Get().CreateRenderBuffer(ivec2(512),PXF_DEPTH);

		fbo[1]->setTexture(m_WaterNormal,COLOR_ATTACHMENT);
		fbo[1]->setRender(m_Depth,DEPTH_ATTACHMENT);

		memset(m_PWave,0,sizeof(WaveParameters)*4);
		memset(m_DWave,0,sizeof(WaveDirections)*4);

		static float overallSteepness = 0.2f;

		// Wave One
		m_PWave[0].speed = 0.05f;
		m_PWave[0].amplitude = 0.02f;
		m_PWave[0].wavelength = 0.3f;
		m_PWave[0].steepness = overallSteepness / (m_PWave[0].wavelength * m_PWave[0].amplitude * 4);
		m_DWave[0].x = +1.0f;
		m_DWave[0].y = +1.5f;

		// Wave Two
		m_PWave[1].speed = 0.1f;
		m_PWave[1].amplitude = 0.01f;
		m_PWave[1].wavelength = 0.4f;
		m_PWave[1].steepness = overallSteepness / (m_PWave[1].wavelength * m_PWave[1].amplitude * 4);
		m_DWave[1].x = +0.8f;
		m_DWave[1].y = +0.2f;

		// Wave Thre
		m_PWave[2].speed = 0.04f;
		m_PWave[2].amplitude = 0.035f;
		m_PWave[2].wavelength = 0.1f;
		m_PWave[2].steepness = overallSteepness / (m_PWave[1].wavelength * m_PWave[1].amplitude * 4);
		m_DWave[2].x = -0.2f;
		m_DWave[2].y = -0.1f;

		// Wave Four
		m_PWave[3].speed = 0.05f;
		m_PWave[3].amplitude = 0.007f;
		m_PWave[3].wavelength = 0.2f;
		m_PWave[3].steepness = overallSteepness / (m_PWave[1].wavelength * m_PWave[1].amplitude * 4);
		m_DWave[3].x = -0.4f;
		m_DWave[3].y = -0.3f;
	}

	Water::~Water()
	{

	}

	void Water::generate()
	{

		std::vector<TVertex> vertices;
		std::vector<TIndex> index;

		float x_2 = size.x/2.0f;
		float y_2 = size.y/2.0f;

		vec2 polysize = vec2(size);
		polysize /= n_poly;

		for(int i = 0; i <= n_poly.x; i++)
		{
			for(int j = 0; j <= n_poly.y; j++)
			{
				TVertex vertex;
				vertex.color = -1;
				vertex.normal = vec3(0.0f,0.0f,1.0f);
				vertex.position = vec3(i*polysize.x-x_2,j*polysize.y-y_2,0.0f);
				vertex.texCoords = vec2(i/((float)n_poly.x),j/((float)n_poly.y));
				vertex.boneCount = 0;
				vertices.push_back(vertex);
			}
		}

		uint32 npoly = n_poly.x*n_poly.y;


		for(int i = 0; i < n_poly.x;i++)
		{
			for(int j = 0; j < n_poly.y; j++)
			{
				int _i = SELECT(i+1, n_poly.x+1), _j = SELECT(j+1, n_poly.y+1);
				index.push_back(i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+_j);

				index.push_back(i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+_j);
				index.push_back(i*(n_poly.y+1)+_j);
			}
		}

		Generate(G_TANGENT,&vertices[0], vertices.size(), &index[0], index.size());

		TDeclarationElement elements[] =
		{
			{0, ELT_USAGE_POSITION,  ELT_TYPE_FLOAT3},
			{0, ELT_USAGE_NORMAL,    ELT_TYPE_FLOAT3},
			{0, ELT_USAGE_DIFFUSE,   ELT_TYPE_COLOR},
			{0, ELT_USAGE_TEXCOORD0, ELT_TYPE_FLOAT2},
			{0, ELT_USAGE_TANGENT,   ELT_TYPE_FLOAT4}
		};
		m_Declaration = Renderer::Get().CreateVertexDeclaration(elements);

		m_VertexBuffer = Renderer::Get().CreateVertexBuffer(vertices.size(), 0, &vertices[0]);
		m_IndexBuffer  = Renderer::Get().CreateIndexBuffer(index.size(), 0, &index[0]);


	}

	void Water::Render() const
	{
		
		GenerateCubeMap();
		GenerateNormal();

		Camera* cam = Renderer::Get().getCamera();
		vec3 dir = cam->getTarget() - cam->getPosition();
		dir = normalize(dir);

		mat4 modelMatrix = m_transfo.ModelMatrix();
		mat3 normalMatrix = mat3(modelMatrix);
		Renderer::Get().SetCurrentProgram(m_program);

		Renderer::Get().LoadMatrix(MAT_MODEL,modelMatrix);
		Renderer::Get().LoadMatrix(MAT_NORMAL, normalMatrix);

		Renderer::Get().SetTexture(0,m_CubeMap.GetTexture(),TEXTURE_CUBE);
		Renderer::Get().SetTexture(2,m_WaterNormal.GetTexture());

		m_program->SetParameter("u_dir",dir);

		Renderer::Get().Enable(RENDER_TEXTURE0,true);
		Renderer::Get().Enable(RENDER_TEXTURE1,true);
		Renderer::Get().Enable(RENDER_TEXTURE2,true);

		Renderer::Get().SetDeclaration(m_Declaration);
		Renderer::Get().SetVertexBuffer(0, m_VertexBuffer);
		Renderer::Get().SetIndexBuffer(m_IndexBuffer);
		Renderer::Get().DrawIndexedPrimitives(m_PrimitiveType, 0, m_IndexBuffer.GetCount());
		Renderer::Get().SetCurrentProgram(NULL);
		Renderer::Get().DebugCubeMap(m_CubeMap.GetTexture());
	}

	void Water::GenerateCubeMap() const
	{
		mat4 view = mat4(1.0f); 
		mat4 projection = perspectiveFov(60.0f, 9.0f, 16.0f, 0.1f, 10000.0f);

		mat4 oldProjection = Renderer::Get().GetMatProjection();
		mat4 oldview = Renderer::Get().GetMatView();

		Renderer::Get().SetMatProjection(projection);
		Renderer::Get().SetViewPort(ivec2(0),ivec2(512));
		for(int nFace = 0; nFace < 6; nFace++) 
		{ 
			vec3 vEnvEyePt = vec3(0.0f, 0.0f, 0.0f); 
			vec3 vLookatPt, vUpVec; 

			switch(nFace) 
			{ 
			case 0: 
			vLookatPt = vec3(1.0f, 0.0f, 0.0f); 
			vUpVec = vec3(0.0f, 1.0f, 0.0f); 
			break; 
			case 1: 
			vLookatPt = vec3(-1.0f, 0.0f, 0.0f); 
			vUpVec = vec3( 0.0f, 1.0f, 0.0f); 
			break; 
			case 2: 
			vLookatPt = vec3(0.0f, 1.0f, 0.0f); 
			vUpVec = vec3(0.0f, 0.0f,-1.0f); 
			break; 
			case 3: 
			vLookatPt = vec3(0.0f,-1.0f, 0.0f); 
			vUpVec = vec3(0.0f, 0.0f, 1.0f); 
			break; 
			case 4: 
			vLookatPt = vec3( 0.0f, 0.0f, 1.0f); 
			vUpVec = vec3( 0.0f, 1.0f, 0.0f); 
			break; 
			case 5: 
			vLookatPt = vec3(0.0f, 0.0f,-1.0f); 
			vUpVec = vec3(0.0f, 1.0f, 0.0f); 
			break; 
			} 
 
			view = lookAt(vEnvEyePt, vLookatPt, vUpVec);
			
			fbo[0]->setTextureCube(m_CubeMap,COLOR_ATTACHMENT,nFace);

			//fbo[0]->Clear();
			fbo[0]->Bind();
			Renderer::Get().SetMatView(view);
			if(scene)
				scene->Draw(SC_DRAW_MODEL | SC_DRAW_TERRAIN | SC_DRAW_SKY);

			fbo[0]->UnBind();
		}

		Renderer::Get().SetMatProjection(oldProjection);
		Renderer::Get().SetMatView(oldview);
		Renderer::Get().SetViewPort(ivec2(0),Renderer::Get().GetScreen());
	}

	void Water::GenerateNormal() const
	{
		mat4 modelMatrix = m_transfo.ModelMatrix();
		mat3 normalMatrix = mat3(modelMatrix);

		mat4 tempProjection = glm::ortho(-(float)size.x/2.0f,(float)size.x/2.0f, -(float)size.y/2.0f,(float)size.y/2.0f);
		//mat4 tempView = lookAt(vec3(0.0f,0.0f,5.0f),vef(0,0,0),vec3(0,0,1));
		fbo[1]->Clear();
		fbo[1]->Bind();
		Renderer::Get().SetCurrentProgram(m_programWaterNormal);
		Renderer::Get().LoadMatrix(MAT_MODEL,modelMatrix);
		Renderer::Get().LoadMatrix(MAT_NORMAL, normalMatrix);
		Renderer::Get().SetViewPort(ivec2(0),ivec2(512));
		m_programWaterNormal->SetParameter("u_waveParameters",(vec4*)m_PWave,4);
		m_programWaterNormal->SetParameter("u_waveDirections",(vec2*)m_DWave,4);
		m_programWaterNormal->SetParameter("projectionMatrix",tempProjection);
		//m_programWaterNormal->SetParameter("viewMatrix",tempView);
		float _time = scene == NULL ? 0 : scene->GetTime();

		m_programWaterNormal->SetParameter("u_passedTime",_time);
		

		Renderer::Get().SetDeclaration(m_Declaration);
		Renderer::Get().SetVertexBuffer(0, m_VertexBuffer);
		Renderer::Get().SetIndexBuffer(m_IndexBuffer);
		Renderer::Get().DrawIndexedPrimitives(m_PrimitiveType, 0, m_IndexBuffer.GetCount());
		Renderer::Get().SetCurrentProgram(NULL);
		fbo[1]->UnBind();
		Renderer::Get().SetViewPort(ivec2(0),Renderer::Get().GetScreen());
	}

	void Water::SetScene(Scene* sc)
	{
		scene = sc;
	}

}
