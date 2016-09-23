#ifndef _ASCENEMGRH_
#define _ASCENEMGRH_
#include <vector>
#include <Core/SceneMgr/Node.h>
#include <Core/Tools/Octree.h>
#define POOL_SIZE 100000


namespace Agmd
{
    class AGMD3D_EXPORT ASceneMgr
    {
    public:
        ASceneMgr()
        {
            m_nodePool.reserve(POOL_SIZE);
            m_transformPool.reserve(POOL_SIZE);
            m_SceneTreePool.reserve(POOL_SIZE);
        }

        ANode* AddNode(Model* model, Material* mat)
        {
            //allocate a new transform;
            m_transformPool.emplace_back();
            Transform* t = &m_transformPool.back();
            m_nodePool.emplace_back(ANode(model, mat, t));

            ANode* n = &m_nodePool.back();
            //allocate a new place in scene tree;

            return n;
        }


        void SetParent(ANode* node, ANode* parent = NULL)
        {
            if (node->m_parent == parent)
                return; // what?
        }

        OcTreeMgr<ANode>& Octree() { return m_octree; }
        //private:

        void AddToSceneTree(ANode* node)
        {
        }

        void TreeMove(a_uint32 offset, a_uint32 to)
        {
            if (to == offset)
                return;
            ANode** node = &m_SceneTreePool[0];

            if (to > offset)
            {
                ANode* tmp = *(node + offset);
                std::memcpy(node + offset, node + offset + 1, to - offset);
                *(node + to) = tmp;
            }
            else
            {
                ANode* tmp = *(node + offset);
                std::memcpy(node + offset, node + offset + 1, to - offset);
                *(node + to) = tmp;
            }
        }

        std::vector<Transform> m_transformPool;
        std::vector<ANode> m_nodePool;
        std::vector<ANode*> m_SceneTreePool; //flat tree (sort by level, parent and address)
        OcTreeMgr<ANode> m_octree;
    };
}

#endif /* */
