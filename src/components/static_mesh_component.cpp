#include "components/static_mesh_component.hpp"

StaticMeshComponent::StaticMeshComponent(const std::string& modelPath, const std::string& texturePath, const Tyra::ObjLoaderOptions& options) 
    : GameComponent("StaticMesh") 
{
    this->modelPath = modelPath;
    this->texturePath = texturePath;
    this->options = options;
}

StaticMeshComponent::~StaticMeshComponent()
{
    this->owner->GetEngine()->renderer.getTextureRepository().freeByMesh(mesh.get());
    TYRA_LOG(owner->GetObjectName(), " -> ", GetComponentName(), " deleted");
}

void StaticMeshComponent::Setup()
{
    auto data = Tyra::ObjLoader::load(Helper::fromCwd(modelPath), options);
    mesh = std::make_unique<Tyra::StaticMesh>(data.get());
    owner->GetEngine()->renderer.getTextureRepository().addByMesh(mesh.get(), Helper::fromCwd(texturePath), "png");
    pipeline.setRenderer(&owner->GetEngine()->renderer.core);
    auto newPosition = owner->GetWorldPosition() + owner->GetLocalPosition();
    newPosition.w = 1.0f;
    mesh->setPosition(newPosition);
    mesh->rotation.rotate(owner->GetWorldRotation() + owner->GetLocalRotation());

    TYRA_LOG(owner->GetObjectName(), " -> ", GetComponentName(), " created");
}

void StaticMeshComponent::Update()
{

}

void StaticMeshComponent::Render()
{
    this->owner->GetEngine()->renderer.renderer3D.usePipeline(pipeline);
    pipeline.render(mesh.get(), &pipelineOptions);
}

void StaticMeshComponent::EventTrigger(ComponentType event, const void* data)
{
    switch (event)
    {
    case ComponentType::Move:
        mesh->translation.translate(*reinterpret_cast<const Tyra::Vec4*>(data));
        return;
    case ComponentType::SetRot:
        mesh->translation.identity();
        mesh->translation.rotate(*reinterpret_cast<const Tyra::Vec4*>(data));
        return;
    case ComponentType::SetPos:
        SetPosition(*reinterpret_cast<const Tyra::Vec4*>(data));
    default:
        return;
    }
}

void StaticMeshComponent::SetPosition(const Tyra::Vec4& newPosition)
{
    mesh->setPosition(newPosition);
}

void StaticMeshComponent::Rotate(const Tyra::Vec4& addedRotation)
{
    mesh->rotation.rotate(addedRotation);
}