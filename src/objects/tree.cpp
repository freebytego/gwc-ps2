#include "objects/tree.hpp"

Tree::Tree(Tyra::Engine* engine)
  : GameObject("Tree", Tyra::Vec4(0.0F, 0.0F, 0.0F), Tyra::Vec4(0.0f, 0.0f, 0.0f), engine)
{
    Setup();
}

Tree::~Tree()
{
    
}

void Tree::Setup() 
{
    RotateObjectLocally(Tyra::Vec4(0, rand() % 360, 0));
    Tyra::ObjLoaderOptions options;
    options.scale = rand() % 3 + 1.f;
    options.flipUVs = true;
    StaticMeshComponent* staticMeshComponent = new StaticMeshComponent("tree/Tree.obj", "tree/", options);
    AddComponent(staticMeshComponent);

    this->staticMeshComponent = staticMeshComponent;
}

void Tree::Update() 
{

}

void Tree::Render()
{
    
}

void Tree::PhysicsUpdate()
{

}