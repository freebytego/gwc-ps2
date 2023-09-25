#ifndef WORLD_H
#define WORLD_H

#include <tyra>
#include "core/tinyphysicsengine.hpp"
#include "core/game_object.hpp"
#include "core/level.hpp"
#include "components/physics_component.hpp"
#include "core/heightmap.hpp"
#include <set>

class Level;

class World : public GameObject 
{
public:
    World(Tyra::Engine* engine);
    ~World();

    void SetLevel(Level* level);
    void ClearLevel();

    static World* GetWorld();
    static void SetWorld(World* world_);

    void AddToCounters(int joints, int connections, int bodies);
    TPE_Body* InitBody(int bodyJoints, int bodyConnections, int bodyMass);
    TPE_Body* InitBody(TPE_Body* body, int bodyMass);

    TPE_Body* MakeCenterRectFull(TPE_Unit width, TPE_Unit depth, TPE_Unit jointSize, TPE_Unit mass);

    Level* GetLevel();

    void AddEnvironmentCollision(int jointIndex);
    void RemoveEnvironmentCollision(TPE_Joint* joint);
    bool GetEnvironmentCollision(TPE_Joint* joint);

    TPE_Vec3 GetLevelEnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance);

private:
    static World* world;

    void Setup() override;
    void Update() override;

    TPE_World tpeWorld;
    TPE_Body* tpeBodies;
    TPE_Joint* tpeJoints;
    TPE_Connection* tpeConnections;

    Level* level = nullptr;

    int usedJoints = 0;
    int usedConnections = 0;

    std::set<TPE_Joint*> envCollisions;
    std::set<TPE_Joint*> lastEnvCollisions;


};

#endif // WORLD_H