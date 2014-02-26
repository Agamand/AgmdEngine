#include "QuadTreeNode.h"
#include "Planet.h"

ivec2 order[]=
{
	ivec2(1,1),
	ivec2(1,-1),
	ivec2(-1,1),
	ivec2(-1,-1)
};

quat GetRotationFor(int divisor, int face)
{
	return quat(glm::rotate(mat4(1),order[face].x*45.f,vec3(1,0,0))/*glm::rotate(mat4(1),order[face].y*45.0f/divisor,vec3(0,1,0))*/);
}
vec3 GetTranslation(int divisor, int face)
{
	return vec3(order[face].x*0.25f,order[face].y*0.25f,0);
}

void QuadTreeNode::FindVisible( Camera*cam, std::vector<DisplayNode*>& display,std::vector<LightNode*>& light )
{
	vec4 point(0,0,0,1);
	point = m_transform->ModelMatrix()*point;
	vec3 real_point = normalize(vec3(point));
	vec3 dist = real_point-cam->GetPosition();
	float distance = length(dist);

	if(m_lod >= MAX_LOD)
	{
		display.push_back(this);
		return;
	}
	if(distance > CONST_DISTANCE/m_divisor)
		display.push_back(this);
	else
	{
		for(int i = 0; i < MAX_FACE; i++)
		{
			if(!face[i])
			{
				Transform* t = new Transform(GetTranslation(m_divisor,i),quat(),vec3(0.5f));
				//t->Rotate(GetRotationFor(m_divisor,i),Transform(vec3(0,0,1)));
				face[i] = new QuadTreeNode(Planet::s_plane,t,m_lod+1);
				face[i]->Update(m_transform,false);
			}
			face[i]->FindVisible(cam,display,light);
		}
	}
}

