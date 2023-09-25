#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include <string>
#include "core/game_object.hpp"

class GameObject;

enum class ComponentType {
    Move,
    SetRot,
    SetPos
};

class GameComponent
{
protected:
    std::string componentName;
    GameObject* owner;
public:
    GameComponent() = default;
    GameComponent(const std::string& name) : componentName(name) {};
    virtual ~GameComponent() {};
    virtual void Setup() {};
    virtual void Update() {};
    virtual void Render() {};
    std::string GetComponentName() { return componentName; }
    virtual void EventTrigger(ComponentType event, const void* data) = 0;
    void SetOwner(GameObject* owner) { this->owner = owner; }
};


#endif // GAME_COMPONENT_H