#ifndef APP_H
#define APP_H

#include <Config\Fwd.h>
#include <Core\AgmdApp.h>
#include <Maths\Vector2.h>
#include <Maths\Vector3.h>
#include <Maths\Matrix4.h>
#include <Utilities\Singleton.h>
#include <Core\Model.h>
#include <Core\ShaderProgram.h>
#include <map>
#include <vector>


struct planete_info
{
	Agmd::Model* model;
	dvec3 velocity;
	double mass;
	double size;
};

class App : public Agmd::AgmdApp, public Agmd::Singleton<App>
{

MAKE_SINGLETON(App)
public:
	static Agmd::Model* CreateSphere(float r,float stack, float slice,float angle, std::string texture);

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
	ModelVector          m_modelVector;
	glm::vec3            m_light_pos;
	Agmd::FrameBuffer*   fbo_shadow;
	Agmd::TextureBase*   tex_shadow;
	Agmd::RenderBuffer*  rbo_shadow;
	Agmd::Texture        tex;
	Agmd::Texture        moon_n;
	Agmd::Texture        moon_h;
	Agmd::Texture        earth_n;
	Agmd::Texture        earth_h;
	Agmd::BaseShaderProgram* tang;
	Agmd::BaseShaderProgram* shader2D;
	Agmd::GraphicString* m_fps;
	planete_info planete_array[2];

};


#endif // APP_H