#ifndef _PLANETATMOSPHERENODE_H_
#define _PLANETATMOSPHERENODE_H_

#include <Core/SceneNode/MeshNode.h>
#include "PlanetModel.h"

class Planet;
class PlanetAtmosphereNode : public MeshNode
{
public:
	PlanetAtmosphereNode(Planet* controller);

	virtual void render( TRenderPass pass ) const;

	virtual void findVisible( Camera*cam, RenderQueue& display, a_vector<LightNode*>& light );

private:
	ShaderProgram m_groundProgram[2];
	ShaderProgram m_skyProgram[2];
	Planet* m_controller;
};


#endif /* _PLANETATMOSPHERENODE_H_ */