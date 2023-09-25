#ifndef CAR_H
#define CAR_H

#include <tyra>

#include "core/game_object.hpp"
#include "core/world.hpp"
#include "core/helper.hpp"
#include "components/static_mesh_component.hpp"
#include "components/physics_component.hpp"

#include "objects/wheel.hpp"
#include "objects/camera.hpp"
#include "objects/ui.hpp"

class CarWheel;

class Car : public GameObject {

public:
    Car(Tyra::Engine* engine);
    ~Car();
    float GetCurrentInputAcceleration();
private:
    float carAcceleration;
    float carTurnRate;
    float carTurnFriction;
    float carForwardFriction;

    void Setup() override;
    void Update() override;
    void Render() override;
    void PhysicsUpdate() override;

    std::vector<CarWheel*> wheels;
    float wheelRotation = 0.f;

    int steering;
    TPE_Vec3 carForw, carSide, carUp, carPos, carRot;

    float acceleration = 0.f;
    float maxAcceleration = 1.4f;
    float minAcceleration = -.85f;

    StaticMeshComponent* staticMeshComponent;
    PhysicsComponent* physicsComponent;
    GameObject* cameraSpot;
    World* world;

    audsrv_adpcm_t* engineSound;
    bool engineSoundChannel = 0;
    u32 engineSoundFramesCounter = 0;
};

#endif