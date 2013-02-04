/*

*/

#ifndef _TRANSFORMMGR_H_
#define _TRANSFORMMGR_H_

#include <Transform.h>

namespace AgmdMaths
{
    class TransformMgr
    {
    public:
        TransformMgr();
        ~TransformMgr();

        void Update();

    private:
        Transform* m_base;
    };
}

#endif // !_TRANSFORMMGR_H_
