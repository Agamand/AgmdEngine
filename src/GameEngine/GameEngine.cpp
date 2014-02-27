#include <GameObject.h>
#include <GameScene.h>
#include <GameEngine.h>


SINGLETON_IMPL(Agmd::GameEngine);

namespace Agmd
{
    GameEngine::GameEngine() :
    m_activeScene(NULL)
    {}


    void GameEngine::SetActiveScene(GameScene* gs)
    {
        m_activeScene = gs;
    }

}