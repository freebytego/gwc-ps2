#ifndef STATIC_MESH_COMPONENT_H
#define STATIC_MESH_COMPONENT_H

#include "core/game_component.hpp"
#include "core/helper.hpp"
#include <tyra>

class StaticMeshComponent : public GameComponent
{

private:
    std::unique_ptr<Tyra::StaticMesh> mesh;
    Tyra::StaPipOptions pipelineOptions;
    Tyra::StaticPipeline pipeline;

    std::string modelPath;
    std::string texturePath;
    Tyra::ObjLoaderOptions options;

public:
    StaticMeshComponent(const std::string& modelPath, const std::string& texturePath, const Tyra::ObjLoaderOptions& options);
    ~StaticMeshComponent();
    void Setup() override;
    void Update() override;
    void Render() override;
    void EventTrigger(ComponentType event, const void* data) override;

    void SetPosition(const Tyra::Vec4& newPosition);
    void Rotate(const Tyra::Vec4& addedRotation);

};


#endif // STATIC_MESH_COMPONENT_H