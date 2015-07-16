#include "Node.h"
#include <Core/Controller/Controller.h>


void Agmd::ANode::SetController( Controller* controller )
{
	m_controller = controller;
	m_controller->m_bindedNode=this;
}

