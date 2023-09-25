#include "objects/car_prop.hpp"

CarProp::CarProp(Tyra::Engine* engine)
  : GameObject("CarProp", Tyra::Vec4(0.0F, 0.0F, 0.0F), Tyra::Vec4(0.0f, 0.0f, 0.0f), engine)
{
    Setup();
}

CarProp::~CarProp()
{
    
}

void CarProp::Setup() 
{
    world = World::GetWorld();
    RotateObjectLocally(Tyra::Vec4(0, -90.f * Tyra::Math::ANG2RAD, 0));
    Tyra::ObjLoaderOptions options;
    options.scale = 1.0F;
    options.flipUVs = true;
    StaticMeshComponent* staticMeshComponent = new StaticMeshComponent("car/Body.obj", "car/body/", options);
    AddComponent(staticMeshComponent);

    this->staticMeshComponent = staticMeshComponent;

    CarWheel* rrWheel = new CarWheel(engine);
    AddChild(rrWheel);
    rrWheel->MoveObjectLocally(Tyra::Vec4(3.7f, -1.f, 2.4f));
    wheels.push_back(rrWheel);

    CarWheel* rlWheel = new CarWheel(engine);
    AddChild(rlWheel);
    rlWheel->MoveObjectLocally(Tyra::Vec4(3.7f, -1.f, -2.4f));
    wheels.push_back(rlWheel);

    CarWheel* frWheel = new CarWheel(engine);
    AddChild(frWheel);
    frWheel->MoveObjectLocally(Tyra::Vec4(-3.7f, -1.f, 2.4f));
    wheels.push_back(frWheel);

    CarWheel* flWheel = new CarWheel(engine);
    AddChild(flWheel);
    flWheel->MoveObjectLocally(Tyra::Vec4(-3.7f, -1.f, -2.4f));
    wheels.push_back(flWheel);
}

void CarProp::Update() 
{

}

void CarProp::Render()
{
    
}

void CarProp::PhysicsUpdate()
{

}