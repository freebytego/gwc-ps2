#include "objects/car.hpp"

Car::Car(Tyra::Engine* engine)
  : GameObject("Car", Tyra::Vec4(0.0F, 0.0F, 0.0F), Tyra::Vec4(0.0f, 0.0f, 0.0f), engine)
{
    Setup();
}

Car::~Car()
{
    delete engineSound;
}

Tyra::Pad* pad;

void Car::Setup() 
{
    world = World::GetWorld();
    RotateObjectLocally(Tyra::Vec4(0, 90.f * Tyra::Math::ANG2RAD, 0));
    Tyra::ObjLoaderOptions options;
    options.scale = 1.0F;
    options.flipUVs = true;
    StaticMeshComponent* staticMeshComponent = new StaticMeshComponent("car/Body.obj", "car/body/", options);
    AddComponent(staticMeshComponent);

    this->staticMeshComponent = staticMeshComponent;

    auto body = World::GetWorld()->MakeCenterRectFull(1000, 1800, 400, 2000);
    PhysicsComponent* physicsComponent = new PhysicsComponent(body);
    AddComponent(physicsComponent);

    this->physicsComponent = physicsComponent;

    // prob should add a way to do this from the PhysicsComponent class, but i am really low on time
    body->joints[4].position.y += 700;
    body->joints[4].sizeDivided *= 3;
    body->joints[4].sizeDivided /= 2;

    World::GetWorld()->InitBody(body, TPE_F);
    
    TPE_bodyMoveBy(body, TPE_vec3(0, 100000.f, 0));

    body->elasticity = TPE_F / 100; 
    body->friction = 3 * TPE_F / 32;
    body->flags |= TPE_BODY_FLAG_ALWAYS_ACTIVE;

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

    cameraSpot = new GameObject("CameraSpot", Tyra::Vec4(0.f), Tyra::Vec4(0.f), engine);
    AddChild(cameraSpot);
    // cameraSpot->MoveObjectLocally(Tyra::Vec4(12.f, 10.f, 0.f));
    // cameraSpot->MoveObjectLocally(Tyra::Vec4(0.f, 300.f, 0.f));

    GameObject* cameraHolder = new GameObject("CameraHolder", Tyra::Vec4(0.f), Tyra::Vec4(0.f), engine);
    cameraSpot->AddChild(cameraHolder);
    cameraHolder->MoveObjectLocally(Tyra::Vec4(15.f, 6.f, 0.f));

    Camera* camera = new Camera(engine);
    Camera::SetCamera(camera);
    camera->SetTarget(this);
    cameraHolder->AddChild(camera);

    engineSound = engine->audio.adpcm.load(Helper::fromCwd("car/engine.adp"));
    engine->audio.adpcm.setVolume(40, 0);
    engine->audio.adpcm.setVolume(40, 1);

    UI* ui = new UI(engine);
    AddChild(ui);

    carAcceleration = TPE_F / 8;
    carTurnRate = 2 * TPE_F / 4;
    carTurnFriction = 3 * TPE_F / 10;
    carForwardFriction = TPE_F / 14;

    pad = &GetEngine()->pad;
}

void Car::Update() 
{
    engineSoundFramesCounter++;
    if (engineSoundFramesCounter > 46 * 2) // 46 is a random number of "average framerate of this game", and 2 is the length of the engine sound in seconds. yeah, hilarious coding here.
    {
        engine->audio.adpcm.tryPlay(engineSound, engineSoundChannel);
        engineSoundChannel = !engineSoundChannel;
        engineSoundFramesCounter = 0;
    }
    auto leftJoystick = pad->getLeftJoyPad();
    auto rightJoystick = pad->getRightJoyPad();

    if (rightJoystick.h <= 100) {
        cameraSpot->RotateObjectLocally(Tyra::Vec4(0.f, 2.f * Tyra::Math::ANG2RAD, 0.f));
    } else if ((rightJoystick.h >= 200)) {
        cameraSpot->RotateObjectLocally(Tyra::Vec4(0.f, -2.f * Tyra::Math::ANG2RAD, 0.f));
    } else {
        cameraSpot->ResetLocalRotation();
    }

    if (leftJoystick.h <= 100) {
        steering = 1;
        // if (wheelRotation < 45.f * Tyra::Math::ANG2RAD)
        // {
        //     wheels[2]->RotateObjectLocally(Tyra::Vec4{0, 2.f * Tyra::Math::ANG2RAD, 0});
        //     wheels[3]->RotateObjectLocally(Tyra::Vec4{0, 2.f * Tyra::Math::ANG2RAD, 0});
        //     wheelRotation += 2.f * Tyra::Math::ANG2RAD;
        // }
    } else if ((leftJoystick.h >= 200)) {
        // if (wheelRotation > -45.f * Tyra::Math::ANG2RAD)
        // {
        //     wheels[2]->RotateObjectLocally(Tyra::Vec4{0, -2.f * Tyra::Math::ANG2RAD, 0});
        //     wheels[3]->RotateObjectLocally(Tyra::Vec4{0, -2.f * Tyra::Math::ANG2RAD, 0});
        //     wheelRotation -= 2.f * Tyra::Math::ANG2RAD;
        // }
        steering = 2;
    } else {
        // auto currentWheelRotation = wheels[2]->GetLocalRotation();
        // currentWheelRotation.lerp(wheels[2]->GetLocalRotation(), Tyra::Vec4{0, 90.f * Tyra::Math::ANG2RAD, 90.f * Tyra::Math::ANG2RAD}, 0.2f);
        // wheelRotation = currentWheelRotation.y - 90.f * Tyra::Math::ANG2RAD;
        // wheels[2]->ResetLocalRotation();
        // wheels[2]->RotateObjectLocally(currentWheelRotation);
        // wheels[3]->ResetLocalRotation();
        // wheels[3]->RotateObjectLocally(currentWheelRotation);
        steering = 0;
    }
    worldPosition = physicsComponent->GetPhysicsPosition();
    worldRotation = physicsComponent->GetPhysicsRotation();

    SetWorldPosition(worldPosition);
    SetWorldRotation(worldRotation);
}

void Car::Render()
{
    
}

void Car::PhysicsUpdate()
{
    auto carBody = physicsComponent->GetBody();
    carForw = TPE_vec3Normalized(TPE_vec3Plus(
      TPE_vec3Minus(carBody->joints[2].position,carBody->joints[0].position),
      TPE_vec3Minus(carBody->joints[3].position,carBody->joints[1].position)));

    carSide = TPE_vec3Normalized(TPE_vec3Plus(
      TPE_vec3Minus(carBody->joints[1].position,carBody->joints[0].position),
      TPE_vec3Minus(carBody->joints[3].position,carBody->joints[2].position)));

    carUp = TPE_vec3Cross(carForw,carSide);

    for (int i = 0; i < 4; ++i)
    {
        if (world->GetEnvironmentCollision(&carBody->joints[i]))
        {
            TPE_Vec3 jv = TPE_vec3(
            carBody->joints[i].velocity[0],   
            carBody->joints[i].velocity[1],   
            carBody->joints[i].velocity[2]);   

            TPE_Vec3 ja = carSide;

            if (i >= 2 && steering)
            {
                if (steering == 2)
                    ja = TPE_vec3Plus(TPE_vec3Times(carForw,carTurnRate),carSide);
                else
                    ja = TPE_vec3Minus(TPE_vec3Times(carForw,carTurnRate),carSide);

                ja = TPE_vec3Normalized(ja);
            }

            TPE_Vec3 fric = TPE_vec3Times(ja,(TPE_vec3Dot(ja,jv) * carTurnFriction)
            / TPE_F);

            jv = TPE_vec3Minus(jv,fric);

            carBody->joints[i].velocity[0] = jv.x;
            carBody->joints[i].velocity[1] = jv.y;
            carBody->joints[i].velocity[2] = jv.z;
        }
    }

    if (TPE_vec3Dot(carUp, TPE_vec3Minus(carBody->joints[4].position, carBody->joints[0].position)) < 0)
    {
        carBody->joints[4].position = TPE_vec3Plus(TPE_vec3Times(carUp, 300), carBody->joints[0].position);
    }

    if (world->GetEnvironmentCollision(&carBody->joints[2]) && world->GetEnvironmentCollision(&carBody->joints[3]))
    {
        if (pad->getPressed().Cross)
        {
            acceleration += 0.03f;
        }
        else if (pad->getPressed().Square)
        {
            acceleration -= 0.15f;
        }
        else
        {
            acceleration -= 0.01f;
            if (acceleration < 0.f) acceleration = 0.f;   
        }

        if (acceleration > maxAcceleration) acceleration = maxAcceleration;
        if (acceleration < minAcceleration) acceleration = minAcceleration;

        carBody->joints[0].velocity[0] += (carForw.x * carAcceleration * acceleration) / TPE_F;
        carBody->joints[0].velocity[1] += (carForw.y * carAcceleration * acceleration) / TPE_F;
        carBody->joints[0].velocity[2] += (carForw.z * carAcceleration * acceleration) / TPE_F;
        carBody->joints[1].velocity[0] += (carForw.x * carAcceleration * acceleration) / TPE_F;
        carBody->joints[1].velocity[1] += (carForw.y * carAcceleration * acceleration) / TPE_F;
        carBody->joints[1].velocity[2] += (carForw.z * carAcceleration * acceleration) / TPE_F;
    }
}

float Car::GetCurrentInputAcceleration()
{   
    return acceleration;
}