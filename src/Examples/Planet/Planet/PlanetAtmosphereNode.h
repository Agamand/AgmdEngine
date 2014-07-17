#ifndef _PLANETATMOSPHERENODE_H_
#define _PLANETATMOSPHERENODE_H_

#include <Core/SceneNode/MeshNode.h>
#include "Planet.h"

class PlanetAtmosphereNode : MeshNode
{
public:
	PlanetAtmosphereNode(Planet* controller);

	virtual void render( TRenderPass pass ) const;

};


#endif /* _PLANETATMOSPHERENODE_H_ */