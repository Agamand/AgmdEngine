#include <Core/RenderObject/GeometryFactory.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Agmd
{
	#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))
	void GeometryFactory::lathe( BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index,int splice )
	{
		a_vector<vec2> _p1 = p1->getComputedPoints();
		a_vector<vec2> _p2 = p2->getComputedPoints();
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
		a_vector<vec2> _p1 = p1->getComputedPoints();
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
			for(int j = 0; j <  ((int)_p1.size()-1);j++)
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
		a_vector<vec2> _p1 = p1->getComputedPoints();
		a_vector<vec2> _p2 = p2->getComputedPoints();
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
		for(int i = 0; i < ((int)_p2.size()-1); i++)
		{
			for(int j = 0; j<  ((int)_p1.size()-1);j++)
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
	Model* GeometryFactory::createPlane(ivec2 size,ivec2 n_poly)
	{

		a_vector<Model::TVertex> vertices;
		a_vector<Model::TIndex> index;

		float x_2 = size.x/2.0f;
		float y_2 = size.y/2.0f;

		vec2 polysize = vec2(size);
		polysize /= n_poly;

		for(int i = 0; i <= n_poly.x; i++)
		{
			for(int j = 0; j <= n_poly.y; j++)
			{
				Model::TVertex vertex;
				vertex.color = -1;
				vertex.normal = vec3(0.0f,0.0f,1.0f);
				vertex.position = vec3(i*polysize.x-x_2,j*polysize.y-y_2,0.0f);
				vertex.texCoords = vec2(i/((float)n_poly.x),j/((float)n_poly.y));
				vertices.push_back(vertex);
			}
		}

		a_uint32 npoly = n_poly.x*n_poly.y;


		for(int i = 0; i < n_poly.x;i++)
		{
			for(int j = 0; j < n_poly.y; j++)
			{
				int _i = SELECT(i+1, n_poly.x+1), _j = SELECT(j+1, n_poly.y+1);
				index.push_back(i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+_j);

				index.push_back(i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+_j);
				index.push_back(i*(n_poly.y+1)+_j);
			}
		}

		return new Model(&vertices[0],vertices.size(),&index[0],index.size());
	}
	#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

	Model* GeometryFactory::createSphere(float r,float stack, float slice,float angle)
	{
		float cosa = 1.0f;
		float sina = 0.0f;
		float cosa1 = cos(angle/stack);
		float sina1 = sin(angle/stack);

		a_vector<Model::TVertex> vertices;
		a_vector<Model::TIndex> index;

		for(int i = 0; i <= stack; i++)
		{
			for(int j = 0; j <= slice; j++)
			{
				Model::TVertex vertex;
				vertex.normal = vec3(cos(i*angle/stack)*sin(j*M_PI/slice),sin(i*angle/stack)*sin(j*M_PI/slice), cos(j*M_PI/slice));
				vertex.position = vec3(r*cos(i*angle/stack)*sin(j*M_PI/slice),r*sin(i*angle/stack)*sin(j*M_PI/slice), r*cos(j*M_PI/slice));
				vertex.texCoords = vec2(i/stack*angle/(M_PI*2),1.0f-j/slice);
				vertices.push_back(vertex);
			}
		}

		for(int i = 0; i < stack;i++)
		{
			for(int j = 0; j < slice; j++)
			{
				/*(i,j+1) _ _ (i+1,j+1)
				|  /|
				| / |
				(i,j)|/  |(i+1,j)
				*/
				int _i = SELECT(i+1,stack+1), _j = SELECT(j+1,(slice+1));

				index.push_back(_i*((int)slice+1)+j);
				index.push_back(i*((int)slice+1)+j);
				index.push_back(_i*((int)slice+1)+_j);

				index.push_back(i*((int)slice+1)+j);
				index.push_back(i*((int)slice+1)+_j);
				index.push_back(_i*((int)slice+1)+_j);
			}
		}
		return new Model(&vertices[0],vertices.size(),&index[0],index.size());
	}


	Model* GeometryFactory::createBox(vec3 size)
	{
		Model::TVertex vertex[] = 
		{    
			//Z+
			{vec3(size.x/2,size.y/2,size.z/2),vec3(0,0,1),-1,vec2(1,0)},
			{vec3(size.x/2,-size.y/2,size.z/2),vec3(0,0,1),-1,vec2(1,1)},
			{vec3(-size.x/2,size.y/2,size.z/2),vec3(0,0,1),-1,vec2(0,0)},
			{vec3(-size.x/2,-size.y/2,size.z/2),vec3(0,0,1),-1,vec2(0,1)},
			//Z-
			{vec3(-size.x/2,-size.y/2,-size.z/2),vec3(0,0,-1),-1,vec2(0,0)},
			{vec3(size.x/2,-size.y/2,-size.z/2),vec3(0,0,-1),-1,vec2(1,0)},
			{vec3(-size.x/2,size.y/2,-size.z/2),vec3(0,0,-1),-1,vec2(0,1)},
			{vec3(size.x/2,size.y/2,-size.z/2),vec3(0,0,-1),-1,vec2(1,1)},
			//X-
			{vec3(-size.x/2,-size.y/2,-size.z/2),vec3(-1,0,0),-1,vec2(0,0)},
			{vec3(-size.x/2,size.y/2,-size.z/2),vec3(-1,0,0),-1,vec2(1,0)},
			{vec3(-size.x/2,-size.y/2,size.z/2),vec3(-1,0,0),-1,vec2(0,1)},
			{vec3(-size.x/2,size.y/2,size.z/2),vec3(-1,0,0),-1,vec2(1,1)},
			//Y+
			{vec3(-size.x/2,size.y/2,-size.z/2),vec3(0,1,0),-1,vec2(0,0)},
			{vec3(size.x/2,size.y/2,-size.z/2),vec3(0,1,0),-1,vec2(1,0)},
			{vec3(-size.x/2,size.y/2,size.z/2),vec3(0,1,0),-1,vec2(0,1)},
			{vec3(size.x/2,size.y/2,size.z/2),vec3(0,1,0),-1,vec2(1,1)},
			//X+
			{vec3(size.x/2,size.y/2,-size.z/2),vec3(1,0,0),-1,vec2(0,0)},
			{vec3(size.x/2,-size.y/2,-size.z/2),vec3(1,0,0),-1,vec2(1,0)},
			{vec3(size.x/2,size.y/2,size.z/2),vec3(1,0,0),-1,vec2(0,1)},
			{vec3(size.x/2,-size.y/2,size.z/2),vec3(1,0,0),-1,vec2(1,1)},
			//Y-
			{vec3(size.x/2,-size.y/2,-size.z/2),vec3(0,-1,0),-1,vec2(0,0)},
			{vec3(-size.x/2,-size.y/2,-size.z/2),vec3(0,-1,0),-1,vec2(1,0)},
			{vec3(size.x/2,-size.y/2,size.z/2),vec3(0,-1,0),-1,vec2(0,1)},
			{vec3(-size.x/2,-size.y/2,size.z/2),vec3(0,-1,0),-1,vec2(1,1)}
		};

		a_vector<Model::TIndex> indices;

		for(a_uint32 i = 0; i < 6; i++)
		{
			indices.push_back(2+i*4);
			indices.push_back(1+i*4);
			indices.push_back(0+i*4);

			indices.push_back(1+i*4);
			indices.push_back(2+i*4);
			indices.push_back(3+i*4);
		}
		return new Model(vertex,4*6,&indices[0],indices.size());
	}

	void GeometryFactory::createPlane(vec3 orientation, quat rot,int size, int offset_index, a_vector<Model::TVertex>& vertices, a_vector<Model::TIndex>& index)
	{
		float x_2 = 1;
		float y_2 = 1;
		vec3 o = -vec3(0.5f,0.5f,0);
		int count = size;
		float offset = 1.f/count;
	
		for(int i = 0; i <= count; i++)
		{
			for(int j = 0; j <= count; j++)
			{
				Model::TVertex vertex;
				vertex.color = -1;
				vertex.normal = orientation;
				vertex.position = orientation/2.f+rot*vec3(o.x+offset*i,o.y+offset*j,0.f);
				vertex.texCoords = vec2(i*offset,j*offset);
				vertices.push_back(vertex);
			}
		}



		for(int i = 0; i < count;i++)
		{
			for(int j = 0; j < count; j++)
			{
				int _i = SELECT(i+1, count+1), _j = SELECT(j+1, count+1);
				index.push_back(offset_index+i*(count+1)+j);
				index.push_back(offset_index+_i*(count+1)+j);
				index.push_back(offset_index+_i*(count+1)+_j);

				index.push_back(offset_index+i*(count+1)+j);
				index.push_back(offset_index+_i*(count+1)+_j);
				index.push_back(offset_index+i*(count+1)+_j);
			}
		}
	}


	Model* GeometryFactory::createMetaSphere(float r, int stack, int slice)
	{
		a_vector<Model::TVertex> vertices;
		a_vector<Model::TIndex> indices;

		quat sRot[] = {
			quat(),
			quat(glm::rotate(mat4(1),180.f,vec3(1,0,0))),
			quat(glm::rotate(mat4(1),90.f,vec3(0,1,0))),
			quat(glm::rotate(mat4(1),-90.f,vec3(0,1,0))),
			quat(glm::rotate(mat4(1),-90.f,vec3(1,0,0))),
			quat(glm::rotate(mat4(1),90.f,vec3(1,0,0)))
		};

		vec3 sOri[] = {
			vec3(0,0,1),
			vec3(0,0,-1),
			vec3(1,0,0),
			vec3(-1,0,0),
			vec3(0,1,0),
			vec3(0,-1,0)
		};

		for(a_uint32 i = 0; i < 6; i++)
			createPlane(sOri[i],sRot[i],20,vertices.size(),vertices,indices);
	
		for(int i = 0; i < (int)vertices.size(); i++)
		{
			vertices[i].position = r*normalize(vertices[i].position);
			vertices[i].normal = vertices[i].position;
		}
		return new Model(&vertices[0],vertices.size(),&indices[0],indices.size());
	}

	float angles(vec2 v1,vec2 v2)
	{
		return acosf(dot(v1,v2)/(length(v1)*length(v2)));
	}

	void GeometryFactory::jarvis( a_vector<vec2>& points, a_vector<vec2>& poly)
	{
		if(!points.size())
			return;
		
		vec2 start = points[0];
		int	i0 = 0;
		for(size_t i = 1, size = points.size(); i < size; i++)
		{
			if(start.x > points[i].x)
			{
				start = points[i];
				i0 = i;
			}else if(start.x == points[i].x && start.y > points[i].y)
			{
				start = points[i];
				i0=i;
			}
		}
		
		vec2 d = vec2(0,-1);
		poly.clear();
		int i = i0;
		do 
		{
			poly.push_back(points[i]);
			int j = !i? 1 : 0;
			vec2 pIJ = points[j]-points[i];
			float amin = angles(d,pIJ);
			float lmax = length(pIJ);
			int in = j;
			for(int j=in+1, n = points.size();j < n; j++)
			{
				if (j != i )
					
				{
					vec2 v = points[j]-points[i];
					float a = angles(d,v);
					if(amin > a || amin == a && lmax < length(v))
					{
						amin = a;
						lmax = length(v);
						in = j;
					}

				}
			}
			d=points[in]-points[i];
			i=in;
		} while (i!=i0);
		poly.push_back(poly[0]);
	}

	bool isIn(vec2 a, vec2 b, vec3 c,vec3 d)
	{
		mat3 mat(a.x-d.x,b.x-d.x,c.x-d.x,a.y-d.y,b.y-d.y,c.y-d.y,(a.x*a.x-d.x*d.x)+(a.y*a.y-d.y*d.y),(b.x*b.x-d.x*d.x)+(b.y*b.y-d.y*d.y),(c.x*c.x-d.x*d.x)+(c.y*c.y-d.y*d.y));
		return 	glm::determinant(mat) > 0;
	}

	void GeometryFactory::delaunay( a_vector<vec2>& points,a_vector<a_uint16>& triangles )
	{
		
	}

	void GeometryFactory::voronoi( a_vector<vec2>& points,a_vector<vec2>& out_points, a_vector<a_uint16>& triangles )
	{

	}

	void GeometryFactory::BBox(a_vector<vec3>& vertices,a_vector<vec3> box)
	{
		
	}


}

