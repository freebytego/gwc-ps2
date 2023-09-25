#include "objects/camera.hpp"

Camera* Camera::camera; 

Camera::Camera(Tyra::Engine* engine)
    : GameObject("Camera", Tyra::Vec4(0.f), Tyra::Vec4(0.f), engine)
{
    Setup();
}

Camera::~Camera()
{

}

void Camera::SetCamera(Camera* camera_)
{
    camera = camera_;
}

Camera* Camera::GetCamera()
{
    return camera;
}

void Camera::SetTarget(GameObject* target)
{
    this->target = target;
}

Tyra::Vec4 Camera::GetTargetLookAt()
{
    return target->GetWorldPosition();
}

