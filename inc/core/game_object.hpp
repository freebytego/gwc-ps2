#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <tyra>
#include <string>
#include <deque>
#include "core/game_component.hpp"

class GameComponent;

class GameObject {

public:
    GameObject() = default;
    GameObject(const std::string& objectName, const Tyra::Vec4& worldPosition, const Tyra::Vec4 worldRotation, Tyra::Engine* engine);
    virtual ~GameObject();

    void SetChildID(size_t id);
    size_t GetChildID();
    void GetObjectName(const std::string& newObjectName);
    std::string GetObjectName();

    void AddChild(GameObject* child);
    void DeleteChildById(size_t id);
    GameObject* GetChildById(size_t id);
    std::deque<GameObject*>* GetChildren();
    GameObject* GetChildByObjectName(const std::string& objectName);

    void AddComponent(GameComponent* component);
    GameComponent* GetComponentById(size_t id);
    GameComponent* GetComponentByObjectName(const std::string& componentName);

    void MoveObjectLocally(const Tyra::Vec4& addition);
    void RotateObjectLocally(const Tyra::Vec4& addition);
    void ResetLocalPosition();
    void ResetLocalRotation();
    Tyra::Vec4 GetLocalPosition();
    Tyra::Vec4 GetLocalRotation();

    void MoveObjectWorld(const Tyra::Vec4& addition);
    void RotateObjectWorld(const Tyra::Vec4& addition);
    void SetWorldPosition(const Tyra::Vec4& position);
    void SetWorldRotation(const Tyra::Vec4& rotation);
    Tyra::Vec4 GetWorldPosition();
    Tyra::Vec4 GetWorldRotation();


    void SetParent(GameObject* parent);
    GameObject* GetParent();
    void RotateWithParent(const Tyra::Vec4& rotation);

    Tyra::Engine* GetEngine() { return this->engine; }

    void _update();
    void _render();
    virtual void PhysicsUpdate() {};
protected:
    GameObject* parent = NULL;

    std::string objectName;
    size_t childId;
    std::deque<GameObject*> children;
    std::deque<GameComponent*> components;

    Tyra::Vec4 localPosition{0.0F, 0.0F, 0.0F, 1.0F};
    Tyra::Vec4 localRotation{0.0F, 0.0F, 0.0F, 1.0F};

    Tyra::Vec4 worldPosition;
    Tyra::Vec4 worldRotation;

    Tyra::StaticPipeline pipeline;
    Tyra::Engine* engine;

    virtual void Setup() {};
    virtual void Update() {};
    virtual void Render() {};

};

#endif