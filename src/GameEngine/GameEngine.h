
#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_
#include <Agmd3D/Core/AgmdApp.h>
#include <GameEngineConfig/ExportGameEngine.h>
#include <GameEngineConfig/FwGameEngine.h>
#include <Utilities/Singleton.h>
#include <vector>

using namespace std;

namespace Agmd
{
    class GAMEENGINE_EXPORT GameEngine : public AgmdApp//, public Singleton<GameEngine>
    {
    public:
    //MAKE_SINGLETON(GameEngine);

    void SetActiveScene(GameScene* gs);

    virtual void OnInit() {}
    virtual void OnUpdate(a_uint64 time_diff) {}
    virtual void OnRender() {}

    private:
        GameEngine();

        GameScene* m_activeScene;

    };
}

#endif /* _GAMEENGINE_H_ */
