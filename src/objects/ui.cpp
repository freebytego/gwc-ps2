#include "objects/ui.hpp"

UI::UI(Tyra::Engine* engine)
    : GameObject("UI", Tyra::Vec4(0.f), Tyra::Vec4(0.f), engine)
{
    Setup();
}

UI::~UI()
{
    
}

void UI::Setup()
{
    auto screenSettings = engine->renderer.core.getSettings();

    minimap = new SpriteComponent("level01/mmap.png", /* As I have only one lvl, I'm just gonna hardcode it here :P GetParent() doesn't work, because the parent is not set yet and same with the level object in the world */
                                                    Tyra::SpriteMode::MODE_STRETCH,
                                                    Tyra::Vec2(15, 20),
                                                    Tyra::Vec2(160.f, 160.f));
    AddComponent(minimap);

    minimapDot = new SpriteComponent("ui/dot.png", 
                                                    Tyra::SpriteMode::MODE_STRETCH,
                                                    Tyra::Vec2(15 + 80, 20 + 80),
                                                    Tyra::Vec2(15.f, 15.f));
    AddComponent(minimapDot);

}

void UI::Update()
{
    if (GetParent())
    {
        // Even more hardcoded stuff. Running low on time!
        auto playerPosition = GetParent()->GetWorldPosition();
        float offsetX = ((playerPosition.x - (-454.7f)) / (392.8f - (-454.7f))) * 160.f + 6.f;
        float offsetZ = ((playerPosition.z - (-326.2f)) / (326.8F - (-326.2f))) * 160.f + 17.f;
        minimapDot->SetPosition(Tyra::Vec2(offsetX, offsetZ));
    }
}

void UI::Render()
{

}