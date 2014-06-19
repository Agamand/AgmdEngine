#ifndef _PLANETMODEL_H_
#define _PLANETMODEL_H_

#include <Core/SceneObject/Model.h>
using namespace Agmd;




class PlanetModel :public Model
{
public:
	PlanetModel(int layer, int x, int y);
	PlanetModel(mat4 matrix);
	static void CreateFaceMetaSphere(std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& indices,int layer,mat4 matrix = mat4(1));
	static void CreatePlane(int size, int offset_index, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index,mat4 matrix);
private:
	int x,y;
};

#endif /* _PLANETMODEL_H_ */