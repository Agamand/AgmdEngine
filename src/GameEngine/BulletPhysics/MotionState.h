#ifndef _MOTIONSTATE_H_

#include <btBulletDynamicsCommon.h>
#include <Transform.h>

using namespace AgmdMaths;
namespace Agmd
{
    class MotionState : public btMotionState {
    public:
        MotionState(Transform* transform);

        virtual ~MotionState();

        virtual void getWorldTransform(btTransform &worldTrans) const {
            worldTrans = mPos1;
        }

        virtual void setWorldTransform(const btTransform &worldTrans) {
            if(NULL == mVisibleobj)
                return; // silently return before we set a node
            btQuaternion rot = worldTrans.getRotation();
            mVisibleobj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
            btVector3 pos = worldTrans.getOrigin();
            mVisibleobj->setPosition(pos.x(), pos.y(), pos.z());
        }

    protected:
        Ogre::SceneNode *mVisibleobj;
        btTransform mPos1;
    }; 
} 

#endif // !1_MOTIONSTATE_H_
