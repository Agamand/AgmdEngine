/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef ICOSAHEDRONMODEL_H
#define ICOSAHEDRONMODEL_H

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Model/Model.h>
#include <vector>

using namespace AgmdMaths;
#define MAX_SUBDIV 5
namespace Agmd
{
	class AGMD3D_EXPORT Icosahedron : public Model
	{
	public :
		typedef unsigned short TIndex;
		Icosahedron(a_uint8 subdiv = 0);

		void setSubdiv(a_uint8);
		a_uint8 getSubdiv() const;

	private:
		a_uint8 m_subdiv;

	};

	typedef SmartPtr<Icosahedron, ResourceCOM> TIcosahedronPtr;

}


#endif // ICOSAHEDRONMODEL_H