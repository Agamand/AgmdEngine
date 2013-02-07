#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_



#include <btBulletDynamicsCommon.h>


using namespace AgmdMaths;

namespace Agmd
{
    /*enum TRANSFORM_SYNC
    {

    };*/
    class RigidBody : public btRigidBody
    {
    public:
        RigidBody(Transform* transform, btCollisionShape* collider);


    private:
        Transform* m_tranform;
    };

    __forceinline void BulletToAgmd(Transform*, const btTransform*);
    __forceinline void AgmdToBullet(btTransform*, const Transform*); 
}


#endif // !_RIGIDBODY_H_
