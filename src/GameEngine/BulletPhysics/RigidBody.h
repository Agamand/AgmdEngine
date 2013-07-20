#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_



#include <btBulletDynamicsCommon.h>
#include <BulletPhysics/MotionState.h>


using namespace AgmdMaths;

namespace Agmd
{
    class RigidBody : public btRigidBody
    {
    public:
        RigidBody(TransformPtr transform, btCollisionShape* collider);


    private:
        TransformPtr m_transform;
    };
}


#endif // !_RIGIDBODY_H_
