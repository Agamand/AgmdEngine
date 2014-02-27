#include <GameScene.h>
#include <vector>

namespace Agmd
{

    GameScene::GameScene()
	{

	}

	GameScene::~GameScene()
    {

	}

    const std::vector<GameObject*>& GameScene::GetGameObjects()
	{
		return m_GameObjects;
	}

    const std::vector<SceneScript*>& GameScene::GetSceneScripts()
	{
		return m_SceneScripts;
	}


	int GameScene::GetGameObjectCount()
	{
		return m_GameObjects.size();
	}


}