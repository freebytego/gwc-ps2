#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "core/game_component.hpp"
#include "core/tinyphysicsengine.hpp"
#include "core/world.hpp"

#define PHYS2TYRA 0.703125f

class World;

class PhysicsComponent : public GameComponent
{

public:
    PhysicsComponent(TPE_Body* body);
    ~PhysicsComponent();
    void EventTrigger(ComponentType event, const void* data) override {};

    Tyra::Vec4 GetPhysicsPosition();
    Tyra::Vec4 GetPhysicsRotation();

    TPE_Body* GetBody();

    void Setup() override;
    void Update() override;
private:
    World* world;
    TPE_Body* body;
    TPE_Vec3 physicsPosition;
    TPE_Vec3 physicsRotation;
};

#endif // PHYSICS_COMPONENT_H