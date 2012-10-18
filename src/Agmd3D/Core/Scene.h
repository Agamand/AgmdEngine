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
		SC_DRAW_SKY		= 0x08,
		SC_DRAW_ALL		= SC_DRAW_MODEL | SC_DRAW_TERRAIN | SC_DRAW_WATER | SC_DRAW_SKY
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

		void Update(uint64 t_diff);

		void AddModel(Model*);
		void AddTerrain(Terrain*);
		void AddWater(Water*);

		void SetSky(Sky*);
		Sky* GetSky();

		void RemoveModel(Model*);
		void RemoveTerrain(Terrain*);
		void RemoveWater(Water*);
		
		float GetTime()
		{
			return m_fTime;
		}

	private:

		vModel	m_vModels;
		vMap	m_vMaps;
		vWater	m_vWaters;
		Sky*	m_Sky;
		float	m_fTime;
	};


}


#endif //SCENE_H