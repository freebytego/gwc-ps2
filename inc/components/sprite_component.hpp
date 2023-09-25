#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <tyra>
#include <string>

#include "core/game_component.hpp"
#include "core/helper.hpp"

class SpriteComponent : public GameComponent
{

public:
    SpriteComponent(const std::string& imagePath, const Tyra::SpriteMode& mode, const Tyra::Vec2 position, const Tyra::Vec2 size);
    ~SpriteComponent();

    void Setup() override;
    void Update() override;
    void Render() override;

    void SetPosition(const Tyra::Vec2 position);
    void SetSize(const Tyra::Vec2 size);

private:
    void EventTrigger(ComponentType event, const void* data) override {};

    std::string imagePath;

    Tyra::Sprite sprite;

};

#endif // SPRITE_COMPONENT_H