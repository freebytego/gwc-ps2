#include "core/level.hpp"

Level::Level(const std::string& basePath, const std::string& modelPath, const std::string& texturePath, const std::string& heightmapPath, Tyra::ObjLoaderOptions options, Tyra::Engine* engine)
    : GameObject("Level", Tyra::Vec4(0.0F, 0.0F, 0.0F), Tyra::Vec4(0.0f, 0.0f, 0.0f), engine)
{
    this->basePath = basePath;

    staticMeshComponent = new StaticMeshComponent(modelPath, texturePath, options);
    AddComponent(staticMeshComponent);

    Setup();
}

Level::Level(Tyra::Engine* engine)
    : GameObject("Level", Tyra::Vec4(0.0F, 0.0F, 0.0F), Tyra::Vec4(0.0f, 0.0f, 0.0f), engine)
{
    this->basePath = basePath;
    Setup();
}

Level::~Level()
{
    
}

void Level::Setup()
{
    
}

void Level::SetGravity(TPE_Unit gravity)
{
    this->gravity = gravity;
}

TPE_Unit Level::GetGravity()
{
    return gravity;
}

std::string Level::GetBasePath()
{
    return basePath;
}