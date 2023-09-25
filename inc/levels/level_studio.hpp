#ifndef TERRAIN_LEVEL_STUDIO_H
#define TERRAIN_LEVEL_STUDIO_H

#include <tyra>
#include <string>

#include "core/tinyphysicsengine.hpp"
#include "core/level.hpp"
#include "core/helper.hpp"

#include "components/sprite_component.hpp"

#include "objects/camera.hpp"

class LevelStudio : public Level // Main Menu
{

public:
    LevelStudio(Tyra::Engine* engine);
    ~LevelStudio();

    TPE_Vec3 EnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance) override;
private:
    void Setup() override;
    void Update() override;
    void Render() override;

    audsrv_adpcm_t* sound;

    int counter = 0;

};

#endif // TERRAIN_LEVEL_STUDIO_H