
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
	Planet(Texture tex[MAX_PLANET_FACE],Material*mat = NULL, float size = 0);

	SceneNode* getRoot()
	{
		return m_root;
	}
	
	Model* exportToFile(const std::string& filename,int precision = 0);

	


	float m_offset;
private:
	Texture m_texture[MAX_PLANET_FACE];
	SceneNode* m_root;
	PlanetModel* m_model;
	Material* m_material;
	
	
	float m_size;
};
#endif
