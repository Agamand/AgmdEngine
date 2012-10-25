
#include "PhysicsMgr.h"
#include "Entities.h"

SINGLETON_IMPL(Agmd::PhysicsMgr);
namespace Agmd
{

	PhysicsMgr::PhysicsMgr() :
	m_uidt(0),
	m_defaultContactProcessingThreshold(BT_LARGE_FLOAT)
	{
		btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration(); 
		btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
		btDbvtBroadphase* broadphase = new btDbvtBroadphase();
		btSequentialImpulseConstraintSolver* sequentialImpulseConstraintSolver = new btSequentialImpulseConstraintSolver();
		m_World = new btDiscreteDynamicsWorld(dispatcher,broadphase,sequentialImpulseConstraintSolver,collisionConfiguration);
		m_World->setGravity( btVector3(0,0,-10) ); 
	}

	void PhysicsMgr::Add(Entities* _entitie)
	{
		m_evEntities.push_back(_entitie);
		m_World->addRigidBody(_entitie->GetBody());
	}

	void PhysicsMgr::Remove(Entities* _entitie)
	{
		
	}

	void PhysicsMgr::Update(uint64 dt)
	{
		m_uidt = dt;

		std::size_t size = m_evEntities.size();

		for(std::size_t i = 0; i < size; i++)
			m_evEntities[i]->Prepare();

		if(m_World)
			m_World->stepSimulation( ((float)dt)/1000.0f, 4);
		
		for(std::size_t i = 0; i < size; i++)
			m_evEntities[i]->Update();
	}

	btRigidBody*	PhysicsMgr::createRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape)
	{
		btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			shape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

	#define USE_MOTIONSTATE 1
	#ifdef USE_MOTIONSTATE
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(mass,myMotionState,shape,localInertia);

		btRigidBody* body = new btRigidBody(cInfo);
		body->setContactProcessingThreshold(m_defaultContactProcessingThreshold);

	#else
		btRigidBody* body = new btRigidBody(mass,0,shape,localInertia);	
		body->setWorldTransform(startTransform);
	#endif//

		return body;
	}

	void PhysicsMgr::DebugDraw()
	{
		m_World->debugDrawWorld();
	}

	void PhysicsMgr::SetGravity(vec3 g)
	{
		m_World->setGravity(btVector3(g.x,g.y,g.z));
	}

}
