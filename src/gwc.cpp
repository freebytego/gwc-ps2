#include "gwc.hpp"

namespace Tyra {

GameWithCar* GameWithCar::gwc;

GameWithCar* GameWithCar::GetGWC()
{
    return gwc;
}

void GameWithCar::SetGWC(GameWithCar* gwc_)
{
    gwc = gwc_;
}

GameWithCar::GameWithCar(Engine* t_engine) : engine(t_engine) {}

GameWithCar::~GameWithCar() {}

void GameWithCar::StartMenu()
{
    shouldStartMenu = true;
}

void GameWithCar::StartGame()
{
    shouldStartGame = true;
}

void GameWithCar::init()
{
    cameraPosition = Vec4(0.0F, 10.0F, -10.0F);

    world = std::make_unique<World>(engine);
    World::SetWorld(world.get());

    LevelStudio* loading = new LevelStudio(engine);
    world->SetLevel(loading);
}

void GameWithCar::loop()
{
    cameraLookAt = Camera::GetCamera()->GetTargetLookAt();
    cameraPosition.lerp(cameraPosition, Camera::GetCamera()->GetWorldPosition(), 0.1f);
    world->_update();
    engine->renderer.beginFrame(CameraInfo3D(&cameraPosition, &cameraLookAt));
    {
        world->_render();
    }
    engine->renderer.endFrame();

    if (shouldStartMenu)
    {
        shouldStartMenu = false;
        if (engine->audio.song.isPlaying())
        {
            engine->audio.song.stop();
        }
        world->ClearLevel();
        LevelMenu* menu = new LevelMenu(engine);
        world->SetLevel(menu);
    }

    if (shouldStartGame)
    {
        if (engine->audio.song.isPlaying())
        {
            engine->audio.song.stop();
        }
        shouldStartGame = false;
        world->ClearLevel();
        Level01* game = new Level01(engine);
        world->SetLevel(game);
    }
}

}
