#include "levels/level_studio.hpp"
#include "gwc.hpp"

LevelStudio::LevelStudio(Tyra::Engine* engine)
    : Level(engine)
{
    TYRA_LOG(this);
    Setup();
}

LevelStudio::~LevelStudio()
{
    delete sound;
}

void LevelStudio::Setup()
{
    GetEngine()->renderer.setClearScreenColor(Tyra::Color(255.f, 255.f, 255.f)); 

    Camera* camera = new Camera(engine);
    Camera::SetCamera(camera);
    camera->SetTarget(this);
    AddChild(camera);

    auto screenSettings = engine->renderer.core.getSettings();

    SpriteComponent* studio = new SpriteComponent("ui/studio.png", 
                                                Tyra::SpriteMode::MODE_STRETCH, 
                                                Tyra::Vec2(screenSettings.getWidth() / 2 - 64.f, screenSettings.getHeight() / 2 - 64.f),
                                                Tyra::Vec2(128.f, 128.f));
    AddComponent(studio);

    sound = engine->audio.adpcm.load(Helper::fromCwd("ui/studio.adp"));
    engine->audio.adpcm.tryPlay(sound, 3);
}

void LevelStudio::Update()
{
    counter++;
    if (counter > 50 * 3)
    {
        counter = -100000; // prevent it from loading multiple times
        Tyra::GameWithCar::GetGWC()->StartMenu();
    }
}

void LevelStudio::Render()
{

}


TPE_Vec3 LevelStudio::EnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance)
{
    return TPE_envGround(position, 0);
}