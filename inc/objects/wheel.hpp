#ifndef WHEEL_H
#define WHEEL_H

#include <tyra>
#include "core/game_object.hpp"
#include "components/static_mesh_component.hpp"
#include "objects/car.hpp"

class CarWheel : public GameObject
{

public:
    CarWheel(Tyra::Engine* engine);
    ~CarWheel() {}

private:
    void Setup() override;
    void Render() override;
    void Update() override;

    StaticMeshComponent* staticMeshComponent;
};

#endif