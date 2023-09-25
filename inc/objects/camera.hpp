#ifndef CAMERA_H
#define CAMERA_H

#include <tyra>

#include "core/game_object.hpp"

class Camera : public GameObject
{
    
public:
    Camera(Tyra::Engine* engine);
    ~Camera();
    static void SetCamera(Camera* camera_);
    static Camera* GetCamera();

    void SetTarget(GameObject* target);
    Tyra::Vec4 GetTargetLookAt();

private:
    static Camera* camera;
    GameObject* target;

};

#endif // CAMERA_H