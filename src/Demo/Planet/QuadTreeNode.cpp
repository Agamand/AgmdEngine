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
	return quat(glm::rotate(mat4(1),order[face].x*45.f/divisor,vec3(1,0,0))*glm::rotate(mat4(1),order[face].y*45.0f/divisor,vec3(0,1,0)));
}

void QuadTreeNode::FindVisible( Camera*cam, std::vector<DisplayNode*>& display,std::vector<LightNode*>& light )
{
	vec4 point(0);
	point = m_transform->ModelMatrix()*point;
	float distance = (vec3(point)-cam->GetPosition()).length();
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
				face[i] = new QuadTreeNode(Planet::s_plane,new Transform(vec3(0,0,0),GetRotationFor(m_divisor,i)),m_lod+1);
			face[i]->FindVisible(cam,display,light);
		}
	}
}

