#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include <GameEngineConfig/FwGameEngine.h>
#include <vector>

namespace Agmd
{
	class GameScene
	{
	public: 
		GameScene();
		~GameScene();
		const std::vector<GameObject*>& GetGameObjects();
        const std::vector<SceneScript*>& GetSceneScripts();
		int GetGameObjectCount();
	private:
		std::vector<GameObject*> m_GameObjects;		
        std::vector<SceneScript*> m_SceneScripts;

	};
}

#endif /* _GAMESCENE_H_ */