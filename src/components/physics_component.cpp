#include "components/physics_component.hpp"

PhysicsComponent::PhysicsComponent(TPE_Body* body)
    : GameComponent("Physics"),
    world(World::GetWorld()),
    body(body)
{
    
}

PhysicsComponent::~PhysicsComponent()
{
    TYRA_LOG(owner->GetObjectName(), " -> ", GetComponentName(), " deleted");
}

void PhysicsComponent::Setup()
{
    TYRA_LOG(owner->GetObjectName(), " -> ", GetComponentName(), " created");
}

void PhysicsComponent::Update()
{
    TPE_bodyApplyGravity(body, world->GetLevel()->GetGravity());
    physicsRotation = TPE_bodyGetRotation(body, 0, 2, 1);
    physicsPosition = TPE_vec3KeepWithinBox(physicsPosition, body->joints[4].position, TPE_vec3(TPE_F / 50,TPE_F / 50,TPE_F / 50));
}

Tyra::Vec4 PhysicsComponent::GetPhysicsPosition()
{   
    return Tyra::Vec4(
        physicsPosition.x / 512.f, 
        physicsPosition.y / 512.f, 
        physicsPosition.z / 512.f,
        1.f);
}

Tyra::Vec4 PhysicsComponent::GetPhysicsRotation()
{
    return Tyra::Vec4(
        physicsRotation.x * PHYS2TYRA * Tyra::Math::ANG2RAD, 
        physicsRotation.y * PHYS2TYRA * -Tyra::Math::ANG2RAD, 
        physicsRotation.z * PHYS2TYRA * Tyra::Math::ANG2RAD, 
        1.0f);
}

TPE_Body* PhysicsComponent::GetBody()
{
    return body;
}