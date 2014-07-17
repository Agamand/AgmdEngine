#include "PlanetAtmosphereNode.h"

#include <Core/RenderObject/GeometryFactory.h>

#define _USE_MATH_DEFINES
#include <math.h>

PlanetAtmosphereNode::PlanetAtmosphereNode(Planet* controller) : MeshNode(GeometryFactory::createSphere(1.025f,80,80,(float)M_PI*2))
{

}

void PlanetAtmosphereNode::render( TRenderPass pass ) const
{
	
}

