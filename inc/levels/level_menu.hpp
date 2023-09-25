#ifndef TERRAIN_LEVEL00_H
#define TERRAIN_LEVEL00_H

#include <tyra>
#include <string>

#include "core/tinyphysicsengine.hpp"
#include "core/heightmap.hpp"
#include "core/level.hpp"
#include "core/helper.hpp"

#include "components/sprite_component.hpp"

#include "objects/camera.hpp"
#include "objects/car_prop.hpp"
#include "objects/tree.hpp"

class LevelMenu : public Level // Main Menu
{

public:
    LevelMenu(Tyra::Engine* engine);
    ~LevelMenu() {};

    TPE_Vec3 EnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance) override;
private:
    void Setup() override;
    void Update() override;
    void Render() override;

};

#endif // TERRAIN_LEVEL00_H