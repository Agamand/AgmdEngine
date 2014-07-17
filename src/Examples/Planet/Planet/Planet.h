
#ifndef _PLANET_H_
#define _PLANET_H_

#include <core/SceneNode/SceneNode.h>

#include "PlanetTreeNode.h"
#include <map>
#include <string>
using namespace Agmd;
#define MAX_PLANET_FACE 6

class Planet
{
public:
	friend class PlanetTreeNode;
	friend class PlanetAtmosphereNode;
	Planet(PlanetModel* model = NULL,Material*mat = NULL, float size = 0);

	SceneNode* getRoot()
	{
		return m_root;
	}
	
	Model* exportToFile(const std::string& filename,int precision = 0, int textureSize = 1024);
	void modelChange()
	{
		for(a_uint32 i = 0; i < MAX_PLANET_FACE; i++)
			if(m_faces[i])
				m_faces[i]->needRegenerateMaps();
	}	


	float m_offset;
private:
	SceneNode* m_root;
	PlanetModel* m_model;
	Material* m_material;
	PlanetTreeNode* m_faces[MAX_PLANET_FACE];
	
	float m_size;
};
#endif
