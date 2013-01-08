#ifndef APP_H
#define APP_H

#include <Agmd3D\Config\Fwd.h>
#include <Agmd3D\Core\AgmdApp.h>
#include <AgmdMaths\Vector2.h>
#include <AgmdMaths\Vector3.h>
#include <AgmdMaths\Matrix4.h>
#include <AgmdUtilities\Utilities\Singleton.h>
#include <Agmd3D\Core\SceneObject\Model.h>
#include <Agmd3D\Core\SceneObject\Displayable.h>
#include <Agmd3D\Core\Shader\ShaderProgram.h>
#include <Agmd3D\Core\GUI\AWindow.h>

#include <map>
#include <vector>

#include <PhysicsPlugin\Entities.h>

class App : public Agmd::AgmdApp, public Singleton<App>
{

MAKE_SINGLETON(App)
public:
    static Agmd::Model* CreateSphere(float r,float stack, float slice,float angle, std::string texture, Agmd::TPrimitiveType type, uint32 color = -1);
    static Agmd::Model* CreatePlane(ivec2 size, ivec2 n_poly, std::string texture, Agmd::TPrimitiveType type);
    static Agmd::Model* CreateBox(vec3 size, std::string texture, Agmd::TPrimitiveType type);
    static Agmd::Model* CreateTriangle(float size, Agmd::TPrimitiveType type);
    Agmd::GraphicString* m_text;

    void Run(int argc, char** argv);
private :

    virtual void OnInit();

    virtual LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
    
    virtual void OnUpdate(uint64 time_diff);
    virtual void OnRender();

    typedef std::map<std::string, std::string> TDescTable;
    typedef std::vector<Agmd::TModelPtr> ModelVector;

    glm::mat4             m_MatProj2D;
    glm::mat4            m_MatProj3D;
    glm::mat3             m_MatNormal;

    Agmd::Scene*        m_Scene;

    Agmd::BaseShaderProgram* shader2D;
    Agmd::GraphicString* m_fps;

    Agmd::Camera*       cam3D;
    Agmd::Camera*       cam2D;

    //TEST 2
    Agmd::AWindow* testwindow;
    Agmd::Texture tex;

    bool pause;
    

};

#endif // APP_H