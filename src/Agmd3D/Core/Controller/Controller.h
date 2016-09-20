/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <CommonDefines.h>

#include <Config/Fwd.h>
#include <Config/Export.h>


namespace Agmd
{
	class ANode;
    class AGMD3D_EXPORT Controller
    {
    friend class ANode;
	friend class SceneNode;
    public:
        Controller() : m_bindedNode((ANode*)(0)){};
        virtual void update(a_uint32 /*time_diff*/) = 0;
    protected:
        ANode*    m_bindedNode;
        
    };

}


#endif /* _CONTROLLER_H_ */