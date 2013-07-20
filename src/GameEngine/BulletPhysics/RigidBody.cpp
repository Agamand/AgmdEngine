#include <BulletPhysics/RigidBody.h>


namespace Agmd
{
    RigidBody::RigidBody(TransformPtr transform, btCollisionShape* collider) :
    btRigidBody(0.0f,new MotionState(transform),collider),
    m_transform(transform)
    {

    }


}