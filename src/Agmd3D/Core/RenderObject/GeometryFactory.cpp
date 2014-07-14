#include <Core/RenderObject/GeometryFactory.h>

namespace Agmd
{
	#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))
	void GeometryFactory::lathe( BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index,int splice )
	{
		std::vector<vec2> _p1 = p1->getComputedPoints();
		std::vector<vec2> _p2 = p2->getComputedPoints();
		vec3 center = vec3(_p2[0],0),
			dir = vec3(_p2[1]-_p2[0],0);

		float offset = 1.f/splice;
		for(int i = 0; i <= splice; i++)
		{
			quat rot = rotate(quat(),360*i*offset,dir);
			for(size_t j = 0; j < _p1.size(); j++)
			{
				Model::TVertex vertex;
				vertex.color = -1;
				vertex.normal = vec3(0,0,1);
				vertex.position = rot*(vec3(_p1[j],0)-center);

				vertex.texCoords = vec2(i/(float)(splice),j/(float)(_p2.size()-1));
				vertices.push_back(vertex);
			}
		}
		int count = _p1.size()-1;
		for(int i = 0; i < splice;i++)
		{
			for(size_t j = 0; j < _p1.size()-1; j++)
			{
				int _i = SELECT(i+1, splice+1), _j = SELECT(j+1, _p1.size());
				index.push_back(i*(count+1)+j);
				index.push_back(_i*(count+1)+j);
				index.push_back(_i*(count+1)+_j);

				index.push_back(i*(count+1)+j);
				index.push_back(_i*(count+1)+_j);
				index.push_back(i*(count+1)+_j);
			}
		}
	}


	void GeometryFactory::simpleExtrusion( BaseSpline* p1, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index, int slice, float scalemin, float scalemax,float height)
	{
		float x_2 = 1;
		float y_2 = 1;
		vec3 o = -vec3(0.5f,0.5f,0);
		std::vector<vec2> _p1 = p1->getComputedPoints();
		vec3 k = vec3(0,0,1);
		vec3 normal = vec3(0);
		bool p1close = p1->isClosed();
		int sizep1 = _p1.size() - (p1close ? 1 : 0);
		float offset = (scalemax-scalemin)/slice;
		float hoffset = (height)/slice;
		for(int i = 0; i <= slice; i++)
		{
			for(int j = 0; j < sizep1; j++)
			{
				Model::TVertex vertex;
				vertex.color = -1;
				vertex.normal = vec3(0,0,1);
				vertex.position = vec3(_p1[j].x,0,_p1[j].y)*(scalemin+offset*i);
				vertex.position.y = i*hoffset;
				vertex.texCoords = vec2(j/(float)(_p1.size()-1),i/(float)(slice));
				vertices.push_back(vertex);
			}
		}

		int count = sizep1-1;
		for(int i = 0; i < slice; i++)
		{
			for(size_t j = 0; j<  (_p1.size()-1);j++)
			{
				int _i = SELECT(i+1, slice+1), _j = SELECT(j+1, sizep1);
				index.push_back(i*(count+1)+j);
				index.push_back(_i*(count+1)+j);
				index.push_back(_i*(count+1)+_j);

				index.push_back(i*(count+1)+j);
				index.push_back(_i*(count+1)+_j);
				index.push_back(i*(count+1)+_j);
			}
		}

	}

	void GeometryFactory::generalizedExtrusion(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index)
	{
		float x_2 = 1;
		float y_2 = 1;
		vec3 o = -vec3(0.5f,0.5f,0);
		std::vector<vec2> _p1 = p1->getComputedPoints();
		std::vector<vec2> _p2 = p2->getComputedPoints();
		//vec3 ori(_p1[0].x,_p2[0].x,_p1[0].y+_p2[0].y);
		vec3 ori;//(_p1[0].x,_p1[0].y+_p2[0].x,_p2[0].y);
		vec3 k = vec3(0,0,1);
		vec3 normal = vec3(0);
		vec2 _T = normalize(_p2[1]-_p2[0]);
		bool p1close = p1->isClosed();
		bool p2close = p2->isClosed();
		int sizep1 = _p1.size() - (p1close ? 1 : 0),sizep2 = _p2.size()- (p2close ? 1 : 0);
		for(int i = 0; i < sizep2; i++)
		{
			if(i == 0 && !p2close)
				_T = normalize(_p2[1]-_p2[0]);
			else if(i == 0 && p2close)
				_T = normalize(_p2[0]-_p2[_p2.size()-2]);
			else
				_T = normalize(_p2[i]-_p2[i-1]);
			for(int j = 0; j < sizep1; j++)
			{

				vec3 tb = vec3(_T.x,_T.y,0);
				vec3 p = cross(tb,vec3(0,0,1));

				Model::TVertex vertex;
				vertex.color = -1;
				vertex.normal = vec3(0,0,1);
				vertex.position = vec3(_p2[i].x,_p2[i].y,0)+vec3(_p1[j].x*p.x,_p1[j].x*p.y,_p1[j].y)-vec3(_p2[0].x,_p2[0].y,0);
				vertex.texCoords = vec2(j/(float)(_p1.size()-1),i/(float)(_p2.size()-1));
				vertices.push_back(vertex);


			}
		}

		int count = sizep1-1;
		for(size_t i = 0; i < (_p2.size()-1); i++)
		{
			for(size_t j = 0; j<  (_p1.size()-1);j++)
			{
				int _i = SELECT(i+1, sizep2), _j = SELECT(j+1, sizep1);
				index.push_back(i*(count+1)+j);
				index.push_back(_i*(count+1)+j);
				index.push_back(_i*(count+1)+_j);

				index.push_back(i*(count+1)+j);
				index.push_back(_i*(count+1)+_j);
				index.push_back(i*(count+1)+_j);
			}
		}

	}
}

