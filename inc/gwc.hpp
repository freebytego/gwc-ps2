#pragma once

#include <tyra>

#include "core/helper.hpp"
#include "core/world.hpp"
#include "core/level.hpp"

#include "objects/car.hpp"
#include "objects/camera.hpp"
#include "levels/level_studio.hpp"
#include "levels/level_menu.hpp"
#include "levels/level01.hpp"

namespace Tyra {

class GameWithCar : public Game {
 public:
  GameWithCar(Engine* engine);
  ~GameWithCar();

  static GameWithCar* GetGWC();
  static void SetGWC(GameWithCar* gwc_);

  void init();
  void loop();

  void StartMenu();
  void StartGame();

 private:
  static GameWithCar* gwc;

  // I don' like this
  bool shouldStartMenu = false;
  bool shouldStartGame = false;

  Engine* engine;
  
  Vec4 cameraPosition, cameraLookAt;
  
  std::unique_ptr<World> world;
};

}  // namespace Tyra
