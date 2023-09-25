#ifndef UI_H
#define UI_H

#include <tyra>

#include "core/game_object.hpp"
#include "core/level.hpp"

#include "components/sprite_component.hpp"

class UI : public GameObject
{

public:
    UI(Tyra::Engine* engine);
    ~UI();

private:
    void Setup() override;
    void Update() override;
    void Render() override;

    SpriteComponent* minimap;
    SpriteComponent* minimapDot;

};

#endif // UI_H