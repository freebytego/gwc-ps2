#include "objects/wheel.hpp"

CarWheel::CarWheel(Tyra::Engine* engine) 
    : GameObject("Wheel", Tyra::Vec4(0.0F, 0.0F, 0.0F), Tyra::Vec4(0.0F, 0.0F, 0.0F), engine) 
{
    Setup();
}

void CarWheel::Setup()
{
    RotateObjectLocally(Tyra::Vec4(0.0F * Tyra::Math::ANG2RAD, 90.0F * Tyra::Math::ANG2RAD, 90.0F * Tyra::Math::ANG2RAD));
    Tyra::ObjLoaderOptions options;
    options.scale = 1.0F;
    options.flipUVs = true;
    StaticMeshComponent* staticMeshComponent = new StaticMeshComponent("car/Wheel.obj", "car/wheel/", options);
    AddComponent(staticMeshComponent);

    this->staticMeshComponent = staticMeshComponent;
}

void CarWheel::Update()
{
    // float carInputAcceleration = dynamic_cast<Car*>(parent)->GetCurrentInputAcceleration();
    // staticMeshComponent->Rotate(Tyra::Vec4(0.0F, -carInputAcceleration * 17.f * Tyra::Math::ANG2RAD, 0.0F));
}

void CarWheel::Render()
{

}