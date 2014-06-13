#ifndef _PLANETMODEL_H_
#define _PLANETMODEL_H_

#include <Core/SceneObject/Model.h>
using namespace Agmd;




class PlanetModel :public Model
{
public:
	PlanetModel(int layer, int x, int y);
	PlanetModel(mat4 matrix);

private:
	int x,y;
};

#endif /* _PLANETMODEL_H_ */