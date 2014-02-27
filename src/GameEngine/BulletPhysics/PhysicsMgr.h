#ifndef _PHYSICSMGR_H_
#define _PHYSICSMGR_H_

#include <BulletPhysics\RigidBody.h>

#include <vector>

#include <CommonDefines.h>

namespace Agmd
{
    class PhysicsMgr
    {
    public:
        PhysicsMgr();
        ~PhysicsMgr();

        void AddRigidBody(RigidBody* rigidbody);
        void RemoveRigidBody(RigidBody* rigidbody);

        void Update(a_uint64 time_diff);
    private:
        std::vector<RigidBody*> m_rigidBody;
    };
}

#endif // !_PHYSICSMGR_H_
