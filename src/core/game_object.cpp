#include "core/game_object.hpp"

GameObject::GameObject(const std::string& objectName, const Tyra::Vec4& worldPosition, const Tyra::Vec4 worldRotation, Tyra::Engine* engine)
{
    this->objectName = objectName;
    this->worldPosition = worldPosition;
    this->worldRotation = worldRotation;
    this->engine = engine;
    TYRA_LOG(GetObjectName(), " created");
    Setup();
}

GameObject::~GameObject()
{
    for (const auto* child : children) {
        delete child;
    }
    for (const auto* component : components) {
        delete component;
    }
    TYRA_LOG(GetObjectName(), " deleted");
}

void GameObject::SetParent(GameObject* parent)
{
    this->parent = parent;
}

GameObject* GameObject::GetParent()
{
    return parent;
}

void GameObject::GetObjectName(const std::string& newObjectName)
{
    objectName = newObjectName;
}
std::string GameObject::GetObjectName()
{
    return objectName;
}

void GameObject::AddChild(GameObject* child)
{
    children.push_back(child);
    child->SetParent(this);
    child->SetChildID(children.size() - 1);
}

void GameObject::DeleteChildById(size_t id)
{
    if (id >= children.size())
    {
        return;
    }
    delete children[id];
    children.erase(children.begin() + id);
}

GameObject* GameObject::GetChildById(size_t id)
{
    if (id >= children.size())
    {
        return NULL;
    }
    return children[id];
}

std::deque<GameObject*>* GameObject::GetChildren()
{
    return &children;
}

GameObject* GameObject::GetChildByObjectName(const std::string& objectName)
{
    for (const auto& child : children)
    {
        if (child->GetObjectName() == objectName)
        {
            return child;
        }
    }
    return NULL;
}

void GameObject::AddComponent(GameComponent* component) {
    components.push_back(component);
    component->SetOwner(this);
    component->Setup();
}

GameComponent* GameObject::GetComponentById(size_t id) {
    if (id >= components.size())
    {
        return NULL;
    }
    return components[id];
}

GameComponent* GameObject::GetComponentByObjectName(const std::string& componentName) {
    for (const auto& component : components)
    {
        if (component->GetComponentName() == componentName)
        {
            return component;
        }
    }
    return NULL;
}


void GameObject::MoveObjectLocally(const Tyra::Vec4& addition)
{
    localPosition += addition;
    MoveObjectWorld(addition);
}

void GameObject::RotateObjectLocally(const Tyra::Vec4& addition)
{
    localRotation += addition;
    RotateObjectWorld(addition);
}

void GameObject::ResetLocalPosition()
{
    worldPosition -= localPosition;
    localPosition = Tyra::Vec4(0.f);
    for (const auto& component : components) {
        component->EventTrigger(ComponentType::SetRot, reinterpret_cast<const void*>(&worldRotation));
        component->EventTrigger(ComponentType::SetPos, reinterpret_cast<const void*>(&worldPosition));
    }
    for (const auto& child : children)
    {
        child->RotateWithParent(Tyra::Vec4(0.f));
    }
}

void GameObject::ResetLocalRotation()
{
    worldRotation -= localRotation;
    localRotation = Tyra::Vec4(0.f);
    for (const auto& component : components) {
        component->EventTrigger(ComponentType::SetRot, reinterpret_cast<const void*>(&worldRotation));
        component->EventTrigger(ComponentType::SetPos, reinterpret_cast<const void*>(&worldPosition));
    }
    for (const auto& child : children)
    {
        child->RotateWithParent(Tyra::Vec4(0.f));
    }
}

void GameObject::MoveObjectWorld(const Tyra::Vec4& addition)
{
    worldPosition += addition;
    for (const auto& component : components) {
        component->EventTrigger(ComponentType::SetRot, reinterpret_cast<const void*>(&worldRotation));
        component->EventTrigger(ComponentType::SetPos, reinterpret_cast<const void*>(&worldPosition));
    }
    for (const auto& child : children)
    {
        child->RotateWithParent(Tyra::Vec4(0.f));
    }
}

void GameObject::RotateObjectWorld(const Tyra::Vec4& addition)
{
    worldRotation += addition;
    for (const auto& component : components) {
        component->EventTrigger(ComponentType::SetRot, reinterpret_cast<const void*>(&worldRotation));
        component->EventTrigger(ComponentType::SetPos, reinterpret_cast<const void*>(&worldPosition));
    }
    for (const auto& child : children)
    {
        child->RotateWithParent(addition);
    }
}

void GameObject::SetWorldPosition(const Tyra::Vec4& position)
{
    worldPosition = position + localPosition;
    worldPosition.w = 1.f;
    for (const auto& component : components) {
        component->EventTrigger(ComponentType::SetRot, reinterpret_cast<const void*>(&worldRotation));
        component->EventTrigger(ComponentType::SetPos, reinterpret_cast<const void*>(&worldPosition));
    }
    for (const auto& child : children)
    {
        child->RotateWithParent(Tyra::Vec4(0.f));
    }
}

void GameObject::SetWorldRotation(const Tyra::Vec4& rotation)
{
    worldRotation = rotation + localRotation;
    for (const auto& component : components) {
        component->EventTrigger(ComponentType::SetRot, reinterpret_cast<const void*>(&worldRotation));
        component->EventTrigger(ComponentType::SetPos, reinterpret_cast<const void*>(&worldPosition));
    }
    for (const auto& child : children)
    {
        child->RotateWithParent(Tyra::Vec4(0.f));
    }
}

void GameObject::_update()
{
    Update();
    for (const auto& component : components) {
        component->Update();
    }
    for (const auto& child : children)
    {
        child->_update();
    }
}

void GameObject::_render()
{
    Render();
    for (const auto& component : components) {
        component->Render();
    }
    for (const auto& child : children)
    {
        child->_render();
    }
}

Tyra::Vec4 GameObject::GetWorldPosition()
{
    return worldPosition;
}

Tyra::Vec4 GameObject::GetWorldRotation()
{
    return worldRotation;
}

Tyra::Vec4 GameObject::GetLocalPosition()
{
    return localPosition;
}

Tyra::Vec4 GameObject::GetLocalRotation()
{
    return localRotation;
}

Tyra::M4x4 multiplyMatrices(const Tyra::M4x4& one, const Tyra::M4x4& two) {
    Tyra::M4x4 res = Tyra::M4x4::Identity; 
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += one.data[i * 4 + k] * two.data[k * 4 + j];
            }
            res.data[i * 4 + j] = sum;
        }
    }
    return res;
}

Tyra::Vec4 multiplyVectorByMatrix(const Tyra::Vec4& vector, const Tyra::M4x4& matrix)
{
    Tyra::Vec4 result;
    result.x = vector.x * matrix.data[0] + vector.y * matrix.data[4] + vector.z * matrix.data[8] + matrix.data[12];
    result.y = vector.x * matrix.data[1] + vector.y * matrix.data[5] + vector.z * matrix.data[9] + matrix.data[13];
    result.z = vector.x * matrix.data[2] + vector.y * matrix.data[6] + vector.z * matrix.data[10] + matrix.data[14];
    return result;
}

void GameObject::RotateWithParent(const Tyra::Vec4& addition)
{
    auto rotation = parent->GetWorldRotation();
    Tyra::M4x4 rotationMatrixX{ 1.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, Tyra::Math::cos(rotation.x), -Tyra::Math::sin(rotation.x), 0.0f,
                                0.0f, Tyra::Math::sin(rotation.x), Tyra::Math::cos(rotation.x), 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f};
    Tyra::M4x4 rotationMatrixY{ Tyra::Math::cos(rotation.y), 0.0f, Tyra::Math::sin(rotation.y), 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                -Tyra::Math::sin(rotation.y), 0.0f, Tyra::Math::cos(rotation.y), 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f};
    Tyra::M4x4 rotationMatrixZ{ Tyra::Math::cos(rotation.z), -Tyra::Math::sin(rotation.z), 0.0f, 0.0f,
                                Tyra::Math::sin(rotation.z), Tyra::Math::cos(rotation.z), 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f};

    auto rotationMatrix = multiplyMatrices(rotationMatrixX, multiplyMatrices(rotationMatrixY, rotationMatrixZ));

    Tyra::Vec4 offset{rotationMatrix.data[0] * localPosition.x + rotationMatrix.data[1] * localPosition.y + rotationMatrix.data[2] * localPosition.z,
    rotationMatrix.data[4] * localPosition.x + rotationMatrix.data[5] * localPosition.y + rotationMatrix.data[6] * localPosition.z,
    rotationMatrix.data[8] * localPosition.x + rotationMatrix.data[9] * localPosition.y + rotationMatrix.data[10] * localPosition.z};

    auto newPosition = offset + parent->GetWorldPosition();
    newPosition.w = 1.0f;
    worldPosition = newPosition;

    auto newRotation = rotation + localRotation;
    newRotation.w = 1.0f;
    worldRotation = newRotation;

    for (const auto& component : components) {
        component->EventTrigger(ComponentType::SetRot, reinterpret_cast<const void*>(&worldRotation));
        component->EventTrigger(ComponentType::SetPos, reinterpret_cast<const void*>(&worldPosition));
    }

    for (const auto& child : children)
    {
        child->RotateWithParent(Tyra::Vec4(0.f));
    }
}

void GameObject::SetChildID(size_t id)
{
    childId = id;
}

size_t GameObject::GetChildID()
{
    return childId;
}
