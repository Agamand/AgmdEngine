#include <CommonDefines.h>
#include <vector>
#include <Transform.h>
#include <Core/Tools/RenderQueue.h>


#ifndef _ARENDERQUEUE_H_
#define _ARENDERQUEUE_H_



using namespace AgmdMaths;
namespace Agmd{

	class Model;
	class ANode;
	class Material;
	struct AGMD3D_EXPORT Drawable
	{
		Drawable(ANode* node);
		Model* model;
		Material* mat;
		Transform transform;
	};

	class AGMD3D_EXPORT ARenderQueue
	{
	public:
		ARenderQueue();
		void  Push(ANode* node);
		void Clear();
		const a_vector<Drawable>&  GetDrawable(TRenderType type = TYPE_DIFFUSE) const;
	private:

		a_vector<Drawable> m_drawable[MAX_TYPE];
	};
}


#endif /*_ARENDERQUEUE_H_*/
