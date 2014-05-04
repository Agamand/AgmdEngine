#ifndef _PLANETMODEL_H_
#define _PLANETMODEL_H_

#include <Core/SceneObject/Model.h>
using namespace Agmd;




class PlanetModel :public Model
{
public:
	PlanetModel(int layer, int x, int y);

private:
	int x,y;
};

#endif /* _PLANETMODEL_H_ */