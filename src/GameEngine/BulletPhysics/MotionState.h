#ifndef _MOTIONSTATE_H_

#include <btBulletDynamicsCommon.h>
#include <Transform.h>

using namespace AgmdMaths;
namespace Agmd
{
    class MotionState : public btMotionState {
    public:
        MotionState(TransformPtr transform) : mVisibleobj(transform)
        {}

        virtual ~MotionState();

        virtual void getWorldTransform(btTransform &worldTrans) const {
            worldTrans.setOrigin(btVector3(mVisibleobj->position.x,mVisibleobj->position.y,mVisibleobj->position.z));
            worldTrans.setRotation(btQuaternion(mVisibleobj->rotation.x, mVisibleobj->rotation.y, mVisibleobj->rotation.z, mVisibleobj->rotation.w));
        }

        virtual void setWorldTransform(const btTransform &worldTrans) {
            if(NULL == mVisibleobj)
                return; // silently return before we set a node
            btQuaternion rot = worldTrans.getRotation();
            btVector3 pos = worldTrans.getOrigin();
            mVisibleobj->SetRotation(quat(rot.w(), rot.x(), rot.y(), rot.z()));
            mVisibleobj->setPosition(vec3(pos.x(), pos.y(), pos.z()));
        }

    protected:
        TransformPtr mVisibleobj;
    }; 
} 

#endif // !1_MOTIONSTATE_H_
