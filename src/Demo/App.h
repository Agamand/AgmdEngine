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
	static Agmd::Model* CreateSphere(float r,float stack, float slice,float angle, std::string texture);
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

	Agmd::Scene*		m_Scene;

	Agmd::BaseShaderProgram* shader2D;
	Agmd::GraphicString* m_fps;

	Agmd::TextureBase* m_ReflectionMap;
	Agmd::TextureBase* m_RefractionMap;
	Agmd::FrameBuffer* fbo[2];

};

#endif // APP_H