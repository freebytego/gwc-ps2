#include "engine.hpp"
#include "gwc.hpp"

int main()
{
  Tyra::EngineOptions opts;
  
  #ifndef RUNNING_FROM_DISC
  opts.loadUsbDriver = true;
  #endif

  opts.writeLogsToFile = false;
  Tyra::Engine engine{opts};
  Tyra::GameWithCar game(&engine);

  Tyra::GameWithCar::SetGWC(&game);

  engine.run(&game);
  return 0;
}
