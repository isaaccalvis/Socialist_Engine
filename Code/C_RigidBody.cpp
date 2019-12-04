#include "Application.h"
#include "C_RigidBody.h"

C_RigidBody::C_RigidBody(GameObject* parent) : Component(parent, COMPONENT_TYPE::COMPONENT_RIGIDBODY)
{
	isUnique = true;
	rigidBody = App->physics->CreateRigidBody(math::float3(1,1,1), mass);
	math::float3 goPosition = parent->GetComponent(COMPONENT_TRANSFORM)->GetComponentAsTransform()->globalPosition;

	btTransform bulletTransform = btTransform::getIdentity();
	bulletTransform.setOrigin(btVector3(goPosition.x, goPosition.y, goPosition.z));

	rigidBody->setCenterOfMassTransform(bulletTransform);
}

C_RigidBody::~C_RigidBody()
{

}

void C_RigidBody::Update(float dt)
{

}

void C_RigidBody::SetMass(float mass)
{
	this->mass = mass;
	rigidBody->setMassProps(mass, btVector3(0,0,0));
}

float C_RigidBody::GetMass() const
{
	return mass;
}