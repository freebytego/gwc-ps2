#ifndef TREE_H
#define TREE_H

#include <tyra>

#include "core/game_object.hpp"
#include "core/world.hpp"
#include "components/static_mesh_component.hpp"

class Tree : public GameObject {

public:
    Tree(Tyra::Engine* engine);
    ~Tree();
private:

    void Setup() override;
    void Update() override;
    void Render() override;
    void PhysicsUpdate() override;

    StaticMeshComponent* staticMeshComponent;
    World* world;

};

#endif