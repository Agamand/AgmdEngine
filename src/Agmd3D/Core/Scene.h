#ifndef SCENE_H
#define SCENE_H

#include <Config\Export.h>
#include <Config\Fwd.h>

#include <AgmdDefines.h>

#include <vector>

namespace Agmd
{
	enum SceneDraw
	{
		SC_NODRAWING	= 0x00,
		SC_DRAW_MODEL	= 0x01,
		SC_DRAW_TERRAIN = 0x02,
		SC_DRAW_WATER   = 0x04,
		SC_DRAW_ALL		= SC_DRAW_MODEL | SC_DRAW_TERRAIN | SC_DRAW_WATER
	};

	typedef std::vector<Model*> vModel;
	typedef std::vector<Terrain*> vMap;
	typedef std::vector<Water*> vWater;

	class AGMD_EXPORT Scene
	{
	public:
		Scene();
		~Scene();

		void Draw(uint32 flag) const;

		void AddModel(Model*);
		void AddTerrain(Terrain*);
		void AddWater(Water*);

		void RemoveModel(Model*);
		void RemoveTerrain(Terrain*);
		void RemoveWater(Water*);

	private:

		vModel	m_vModels;
		vMap	m_vMaps;
		vWater	m_vWaters;
	};


}


#endif //SCENE_H