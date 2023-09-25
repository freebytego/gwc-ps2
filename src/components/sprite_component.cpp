#include "components/sprite_component.hpp"

SpriteComponent::SpriteComponent(const std::string& imagePath, const Tyra::SpriteMode& mode, const Tyra::Vec2 position, const Tyra::Vec2 size)
    : GameComponent("SpriteComponent")
{
    sprite.mode = mode;
    sprite.position = position;
    sprite.size = size;
    this->imagePath = imagePath;
}

SpriteComponent::~SpriteComponent()
{
    TYRA_LOG(owner->GetObjectName(), " -> ", GetComponentName(), " deleted");
    owner->GetEngine()->renderer.getTextureRepository().freeBySprite(sprite);
}

void SpriteComponent::Setup()
{
    auto texture = owner->GetEngine()->renderer.getTextureRepository().add(Helper::fromCwd(imagePath));
    texture->addLink(this->sprite.id);
    TYRA_LOG(owner->GetObjectName(), " -> ", GetComponentName(), " created");
}

void SpriteComponent::Update()
{

}

void SpriteComponent::Render()
{
    owner->GetEngine()->renderer.renderer2D.render(sprite);
}

void SpriteComponent::SetPosition(const Tyra::Vec2 position)
{
    sprite.position = position;
}

void SpriteComponent::SetSize(const Tyra::Vec2 size)
{
    sprite.size = size;
}
