#ifndef TERRAIN_LEVEL01_H
#define TERRAIN_LEVEL01_H

#include <tyra>
#include <string>

#include "core/tinyphysicsengine.hpp"
#include "core/tinyphysicsengine.hpp"
#include "core/heightmap.hpp"
#include "core/level.hpp"
#include "core/helper.hpp"

#include "objects/car.hpp"

class Level01 : public Level
{

public:
    Level01(Tyra::Engine* engine);
    ~Level01() {};

    TPE_Vec3 EnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance) override;
private:
    void Setup() override;
    void Update() override;
    void Render() override;

};

#endif // TERRAIN_LEVEL01_H