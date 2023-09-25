#ifndef TERRAIN_H
#define TERRAIN_H

#include <tyra>
#include <string>

#include "core/tinyphysicsengine.hpp"
#include "core/heightmap.hpp"
#include "core/world.hpp"
#include "core/game_object.hpp"
#include "components/static_mesh_component.hpp"

class Level : public GameObject 
{

public:
    Level(const std::string& basePath, const std::string& modelPath, const std::string& texturePath, const std::string& heightmapPath, Tyra::ObjLoaderOptions options, Tyra::Engine* engine);
    Level(Tyra::Engine* engine);
    virtual ~Level() = 0;
    virtual TPE_Vec3 EnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance) = 0;

    void SetGravity(TPE_Unit gravity);
    TPE_Unit GetGravity();
    std::string GetBasePath();

private:
    virtual void Setup();
    virtual void Update() {}
    virtual void Render() {}
    StaticMeshComponent* staticMeshComponent;

    std::string basePath;
    TPE_Unit gravity = TPE_F / 50;
};

#endif // TERRAIN_H