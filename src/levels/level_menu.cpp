#include "levels/level_menu.hpp"
#include "gwc.hpp"

LevelMenu::LevelMenu(Tyra::Engine* engine)
    : Level("menu/", "menu/menu.obj", "menu/", "", Tyra::ObjLoaderOptions{}, engine)
{
    Setup();
}

void LevelMenu::Setup()
{
    GetEngine()->renderer.setClearScreenColor(Tyra::Color(203.f, 239.f, 245.f));

    Tree* tree = new Tree(engine);
    tree->MoveObjectWorld(Tyra::Vec4(-10.f, 0, 0));
    AddChild(tree);

    CarProp* carProp = new CarProp(engine);
    AddChild(carProp);    

    carProp->MoveObjectWorld(Tyra::Vec4(0, 2.f, 0));

    Camera* camera = new Camera(engine);
    Camera::SetCamera(camera);
    camera->SetTarget(this);
    camera->SetWorldPosition(Tyra::Vec4(20.f, 20.f, -20.f));
    AddChild(camera);

    auto screenSettings = engine->renderer.core.getSettings();
    SpriteComponent* logo = new SpriteComponent("ui/logo.png", 
                                                Tyra::SpriteMode::MODE_STRETCH, 
                                                Tyra::Vec2(40, 0),
                                                Tyra::Vec2(160.f, 160.f));
    AddComponent(logo);

    SpriteComponent* studio = new SpriteComponent("ui/studio.png", 
                                                Tyra::SpriteMode::MODE_STRETCH, 
                                                Tyra::Vec2(screenSettings.getWidth() - 100, screenSettings.getHeight() - 80),
                                                Tyra::Vec2(64.f, 64.f));
    AddComponent(studio);

    SpriteComponent* play = new SpriteComponent("ui/play.png", 
                                                Tyra::SpriteMode::MODE_STRETCH, 
                                                Tyra::Vec2(0, screenSettings.getHeight() / 2 - 32),
                                                Tyra::Vec2(64.f, 64.f));
    AddComponent(play);


    engine->audio.song.load(Helper::fromCwd("music/menu.wav"));
    engine->audio.song.inLoop = true;
    engine->audio.song.setVolume(90); // for funnies im gonna make main menu way louder than the game song :)
    engine->audio.song.play();

}

void LevelMenu::Update()
{
    if (engine->pad.getClicked().Cross)
    {
        Tyra::GameWithCar::GetGWC()->StartGame();
    }
}

void LevelMenu::Render()
{

}


TPE_Vec3 LevelMenu::EnvironmentDistance(TPE_Vec3 position, TPE_Unit maxDistance)
{
    return TPE_envGround(position, 0);
}