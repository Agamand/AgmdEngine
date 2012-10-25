#ifndef APP_H
#define APP_H

#include <Agmd3D\Config\Fwd.h>
#include <Agmd3D\Core\AgmdApp.h>
#include <AgmdMaths\Vector2.h>
#include <AgmdMaths\Vector3.h>
#include <AgmdMaths\Matrix4.h>
#include <AgmdUtilities\Utilities\Singleton.h>
#include <Agmd3D\Core\Model.h>
#include <Agmd3D\Core\Shader\ShaderProgram.h>
#include <Agmd3D\Core\GUI\AWindow.h>



#include <map>
#include <vector>


struct planete_info
{
	Agmd::Model* model;
	dvec3 velocity;
	double mass;
	double size;
};

class App : public Agmd::AgmdApp, public Singleton<App>
{

MAKE_SINGLETON(App)
public:
	static Agmd::Model* CreateSphere(float r,float stack, float slice,float angle, std::string texture, Agmd::TPrimitiveType type);
	static Agmd::Model* CreatePlane(ivec2 size, ivec2 n_poly, std::string texture, Agmd::TPrimitiveType type);
	static Agmd::Model* CreateTriangle(float size, Agmd::TPrimitiveType type);
	Agmd::GraphicString* m_text;
private :

    virtual void OnInit();

    virtual LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
	
    virtual void OnUpdate(uint64 time_diff);
    virtual void OnRender();

    typedef std::map<std::string, std::string> TDescTable;
	typedef std::vector<Agmd::TModelPtr> ModelVector;


	
    glm::mat4            m_MatView2D;
    glm::mat4            m_MatView3D;
    glm::mat4		     m_MatProj2D;
    glm::mat4            m_MatProj3D;
	glm::mat3			 m_MatNormal;
	glm::vec3            m_light_pos;
	glm::vec3            m_light_dir;
	float				 m_light_angle;
	float				 m_tesslationInner;
	float				 m_tesslationOuter;
	float				 height;

	Agmd::Scene*		m_Scene;

	Agmd::BaseShaderProgram* shader2D;
	Agmd::GraphicString* m_fps;




	//TESS TEST

	Agmd::Buffer<float>	   m_vbuffer;
	Agmd::Buffer<short>	   m_ibuffer;
	Agmd::DeclarationPtr   m_d;

	Agmd::BaseShaderProgram* tesselation_shader;
	Agmd::BaseShaderProgram* simple_shader;
	Agmd::Model* sphere[2];
	

	//TEST 2
	Agmd::TextureBase* buffer[2];
	Agmd::FrameBuffer* fbo[2];

	Agmd::TextureBase* use_buffer;
	Agmd::FrameBuffer* use_fbo;
	Agmd::AWindow* testwindow;
	

};

#endif // APP_H