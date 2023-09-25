#ifndef CAR_PROP_H
#define CAR_PROP_H

#include <tyra>

#include "core/game_object.hpp"
#include "core/world.hpp"
#include "components/static_mesh_component.hpp"
#include "components/physics_component.hpp"

#include "objects/wheel.hpp"

class CarWheel;

class CarProp : public GameObject {

public:
    CarProp(Tyra::Engine* engine);
    ~CarProp();
private:

    void Setup() override;
    void Update() override;
    void Render() override;
    void PhysicsUpdate() override;

    std::vector<CarWheel*> wheels;

    StaticMeshComponent* staticMeshComponent;
    PhysicsComponent* physicsComponent;
    World* world;

};

#endif