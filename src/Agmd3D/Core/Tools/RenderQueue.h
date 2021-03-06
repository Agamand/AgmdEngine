#ifndef _RENDERQUEUE_H_
#define _RENDERQUEUE_H_

#include <Config/Export.h>
#include <Container/Vector.h>

namespace Agmd
{
#define MAX_TYPE 2
    class DisplayNode;

    enum TRenderType
    {
        TYPE_DIFFUSE,
        TYPE_BLEND
    };

    class AGMD3D_EXPORT RenderQueue
    {
    public:
        friend class SceneMgr;


        RenderQueue()
        {
        }

        void push_back(DisplayNode* node, TRenderType type = TYPE_DIFFUSE)
        {
            if (type < 0 || type >= MAX_TYPE)
                return;
            m_displayable[type].push_back(node);
        }

        void clear()
        {
            for (a_uint32 i = 0; i < MAX_TYPE; i++)
                m_displayable[i].clear();
        }

        const a_vector<DisplayNode*>& getDisplayable(TRenderType type = TYPE_DIFFUSE) const
        {
            return m_displayable[type];
        }

    private:
        a_vector<DisplayNode*> m_displayable[MAX_TYPE];
    };
}

#endif
