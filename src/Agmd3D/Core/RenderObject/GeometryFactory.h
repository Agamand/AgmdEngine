


#ifndef _GEOMETRYFACTORY_H_
#define _GEOMETRYFACTORY_H_

#include <Core/2DRender/BaseSpline.h>
#include <Core/SceneObject/Model.h>

namespace Agmd
{
	class GeometryFactory
	{
	public:
		void lathe(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index,int splice);
		void simpleExtrusion( BaseSpline* p1, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index, int slice, float scalemin, float scalemax,float height);
		void generalizedExtrusion(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index);
	};
}

#endif /* _GEOMETRYFACTORY_H_ */