
#include "core/world.hpp"
#include <sstream>

#include "levels/level01.hpp"

World* World::world;

int collisionCallback(int b1, int j1, int b2, int j2, TPE_Vec3 p)
{
    if (b1 == b2)
    {
        World::GetWorld()->AddEnvironmentCollision(j1);
    }
    return 1;
}

TPE_Vec3 environmentDistance(TPE_Vec3 p, TPE_Unit maxD)
{
    // return TPE_envGround(p, 0);
    return World::GetWorld()->GetLevelEnvironmentDistance(p, maxD);
}

World* World::GetWorld()
{
    return world;
}

void World::SetWorld(World* world_)
{
    world = world_;
}

World::World(Tyra::Engine* engine) 
    : GameObject("World", Tyra::Vec4(0.0F, 0.0F, 0.0F), Tyra::Vec4(0.0f, 0.0f, 0.0f), engine)
{
    Setup();
}

World::~World()
{
    delete[] tpeConnections;
    delete[] tpeJoints;
    delete[] tpeBodies;
}

void World::Setup()
{
    tpeBodies = new TPE_Body[10];
    tpeJoints = new TPE_Joint[128];
    tpeConnections = new TPE_Connection[256];
    TPE_worldInit(&tpeWorld,tpeBodies,0,0);
    tpeWorld.environmentFunction = environmentDistance;
    tpeWorld.collisionCallback = collisionCallback;
}

void World::SetLevel(Level* level)
{
    TYRA_ASSERT(this->level == nullptr, "Current level is not null");
    AddChild(level);
    this->level = level;
}

void World::ClearLevel()
{
    TYRA_ASSERT(this->level != nullptr, "Current level is null");

    DeleteChildById(this->level->GetChildID());

    usedJoints = 0;
    usedConnections = 0;
    envCollisions.clear();
    lastEnvCollisions.clear();

    delete[] tpeConnections;
    delete[] tpeJoints;
    delete[] tpeBodies;

    level = nullptr;

    Setup();
}

void World::Update()
{
    for (const auto& child : *level->GetChildren()) // YUCK
    {
        PhysicsComponent* pc = dynamic_cast<PhysicsComponent*>(child->GetComponentByObjectName("Physics"));
        if (pc)
        {
            child->PhysicsUpdate();
        }
    }
    envCollisions.clear();
    TPE_worldStep(&tpeWorld);
    lastEnvCollisions = envCollisions;
}

TPE_Body* World::InitBody(int bodyJoints, int bodyConnections, int bodyMass)
{
    TPE_bodyInit(&tpeBodies[tpeWorld.bodyCount], &tpeJoints[usedJoints], bodyJoints, &tpeConnections[usedConnections], bodyConnections, bodyMass);
    usedConnections += bodyConnections;
    usedJoints += bodyJoints;
    tpeWorld.bodyCount++;
    return &tpeWorld.bodies[tpeWorld.bodyCount - 1];
}

TPE_Body* World::InitBody(TPE_Body* body, int bodyMass)
{
    TPE_bodyInit(body, body->joints, body->jointCount, body->connections, body->connectionCount, bodyMass);
    return &tpeWorld.bodies[tpeWorld.bodyCount - 1];
}

void World::AddToCounters(int joints, int connections, int bodies)
{
    usedConnections += connections;
    usedJoints += joints;
    tpeWorld.bodyCount += bodies;
}

TPE_Body* World::MakeCenterRectFull(TPE_Unit width, TPE_Unit depth, TPE_Unit jointSize, TPE_Unit mass)
{
    TPE_makeCenterRectFull(tpeJoints + usedJoints, tpeConnections + usedConnections, width, depth, jointSize);
    return InitBody(5, 10, mass);
}

Level* World::GetLevel()
{
    return level;
}

void World::AddEnvironmentCollision(int jointIndex)
{
    envCollisions.insert(&tpeJoints[jointIndex]);
}

void World::RemoveEnvironmentCollision(TPE_Joint* joint)
{
    if (envCollisions.count(joint))
    {
        envCollisions.erase(joint);
    }
}

bool World::GetEnvironmentCollision(TPE_Joint* joint)
{
    return envCollisions.count(joint) || lastEnvCollisions.count(joint);
}

TPE_Vec3 World::GetLevelEnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance)
{
    return level->EnvironmentDistance(position, maxDistance);
}