#include "Entities.h"

namespace Agmd
{
	Entities::Entities(float _mass, btCollisionShape* _shape , PhysicsTransfo& _transfo,EntitiesType _type) : 
	m_Tranfo(_transfo),
	m_Type(_type),
	m_fMass(_mass),
	m_Shape(_shape)
	{
		Init();
	}

	void Entities::Init()
	{
		btAssert((!m_Shape || m_Shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

		bool isDynamic = (m_fMass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			m_Shape->calculateLocalInertia(m_fMass,localInertia);

		btVector3 _pos = btVector3(m_Tranfo.m_position.x,m_Tranfo.m_position.y,m_Tranfo.m_position.z);
		btQuaternion _rotation = btQuaternion(m_Tranfo.m_rotation.x,m_Tranfo.m_rotation.y,m_Tranfo.m_rotation.z,m_Tranfo.m_rotation.w);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(btTransform(_rotation,_pos));

		btRigidBody::btRigidBodyConstructionInfo cInfo(m_fMass,myMotionState,m_Shape,localInertia);

		m_Rigid = new btRigidBody(cInfo);
		m_Rigid->setContactProcessingThreshold(BT_LARGE_FLOAT);
		m_Rigid->setFriction(1.0f);
	}

	void Entities::Prepare()
	{
		btVector3 _pos = btVector3(m_Tranfo.m_position.x,m_Tranfo.m_position.y,m_Tranfo.m_position.z);
		btQuaternion _rotation = btQuaternion(m_Tranfo.m_rotation.x,m_Tranfo.m_rotation.y,m_Tranfo.m_rotation.z,m_Tranfo.m_rotation.w);
		
		m_Rigid->getWorldTransform().setOrigin(_pos);
		m_Rigid->getWorldTransform().setRotation(_rotation);
	}

	void Entities::Update()
	{
		btVector3 _pos;
		btQuaternion _rotation;

		_pos = m_Rigid->getWorldTransform().getOrigin();
		_rotation = m_Rigid->getWorldTransform().getRotation();
		m_Tranfo.m_position.x = _pos.x();
		m_Tranfo.m_position.y = _pos.y();
		m_Tranfo.m_position.z = _pos.z();

		m_Tranfo.m_rotation.x = _rotation.x();
		m_Tranfo.m_rotation.y = _rotation.y();
		m_Tranfo.m_rotation.z = _rotation.z();
		m_Tranfo.m_rotation.w = _rotation.w();
		
	}
	void Entities::SetVelocity(vec3 _velocity)
	{
		m_Rigid->setLinearVelocity(btVector3(_velocity.x,_velocity.y,_velocity.z));
	}
}