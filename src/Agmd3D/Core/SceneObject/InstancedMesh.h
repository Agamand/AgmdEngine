#ifndef _INSTANCEDMESH_H_
#define _INSTANCEDMESH_H_

#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/Displayable.h>


namespace Agmd
{
	class InstancedMesh : public Displayable
	{
	public:
		InstancedMesh(Model* model = NULL);
		InstancedMesh(std::string name);
		virtual ~InstancedMesh();
		
		virtual void Render() const;

	private:
		Model* model;
	}
}

#endif