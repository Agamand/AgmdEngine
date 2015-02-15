#include <Editor/ObjectPropertyGrid.h>
#include <Core/Model/IcosahedronModel.h>

void ObjectPropertyGrid::setCurrent( Agmd::SceneNode* node )
{
	Clear();
	m_current = node;
	if(m_current != NULL)
	{
		switch(node->getType())
		{
		case Agmd::NodeType::ROOT_NODE:
			buildProperty((Agmd::RootNode*)node);
			break;
		case Agmd::NodeType::DISPLAYABLE_NODE:
			buildProperty((Agmd::DisplayNode*)node);
			break;
		case Agmd::NodeType::MESH_NODE:
			buildProperty((Agmd::MeshNode*)node);
			break;
		case Agmd::NodeType::CAMERA_NODE:
			buildProperty((Agmd::CameraNode*)node);
			break;
		default:
			buildProperty(node);
		}

	}
}

void ObjectPropertyGrid::buildProperty(Agmd::SceneNode* node)
{
	Append( new wxPropertyCategory( wxT("SceneNode"), wxT("SceneNode") ) ); 
}

void ObjectPropertyGrid::buildProperty(Agmd::RootNode* node)
{
	buildProperty((Agmd::SceneNode*)node);
	Append( new wxPropertyCategory( wxT("RootNode"), wxT("RootNode") ) ); 
}

void ObjectPropertyGrid::buildProperty(Agmd::DisplayNode* node)
{
	buildProperty((Agmd::SceneNode*)node);
	Append( new wxPropertyCategory( wxT("DisplayNode"), wxT("DisplayNode") ) );
}

void ObjectPropertyGrid::buildProperty(Agmd::MeshNode* node)
{
	buildProperty((Agmd::DisplayNode*)node);
	Append( new wxPropertyCategory( wxT("MeshNode"), wxT("MeshNode") ) );
	Agmd::Icosahedron* m;
	if((m = dynamic_cast<Agmd::Icosahedron*>(node->getModel())))
	{
		wxIntProperty* p =new wxIntProperty( wxT("subdivision"), wxT("subdivision"),m->getSubdiv());
		Append(p);
	}

}



void ObjectPropertyGrid::buildProperty(Agmd::CameraNode* node)
{
	buildProperty((Agmd::SceneNode*)node);
	Append( new wxPropertyCategory( wxT("CameraNode"), wxT("CameraNode") ) );
}
