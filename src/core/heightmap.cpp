/*
# _____        ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licensed under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "core/heightmap.hpp"

#include <sstream>

using Tyra::FileUtils;
using Tyra::PngLoader;
using Tyra::PngPixel3;
using Tyra::Vec4;

Heightmap::Heightmap(const float& t_minHeight, const float& t_maxHeight,
                     const Vec4& t_leftUp, const Vec4& t_rightDown)
    : minHeight(t_minHeight),
      maxHeight(t_maxHeight),
      leftUp(t_leftUp),
      rightDown(t_rightDown) {
  std::ifstream heightmapFile;
  // testing

  heightmapFile.open(Helper::fromCwd("level01/heightmap.csv"));
  TYRA_ASSERT(heightmapFile.is_open(), "Failed to open the heightmap");

  std::string line, val;
  while (std::getline(heightmapFile, line)) {
    std::vector<float> v;
    std::stringstream s(line);
    while (getline(s, val, ';')) {
      v.push_back(std::stof(val));
    }
    heightmapData.push_back(v);
  }

  heightmapFile.close();

  mapWidth = heightmapData[0].size();
  mapHeight = heightmapData.size();

  PngLoader loader;
  auto* data = loader.load(Helper::fromCwd("level01/heightmap.png"));
  // allocateMap(data->data, data->width, data->height);

  delete data;
}

bool Heightmap::isOutside(const Vec4& position) const {
  return position.x <= leftUp.x || position.x >= rightDown.x ||
         position.z <= leftUp.z || position.z >= rightDown.z;
}

Heightmap::~Heightmap() {

}

float Heightmap::getHeightOffset(const Vec4& playerPosition) const {
  float widthPercentage = getWidthPercentage(playerPosition);
  float heightPercentage = getHeightPercentage(playerPosition);
  auto x = static_cast<int>(widthPercentage * mapWidth);
  auto y = static_cast<int>(heightPercentage * mapHeight);

  if (!(x >= 0 && x < mapWidth) || !(y >= 0 && y < mapHeight)) {
    TYRA_LOG("RIP");
    return heightmapData[0][0];
  }

  TYRA_ASSERT(x >= 0 && x < mapWidth, "x is out of range");
  TYRA_ASSERT(y >= 0 && y < mapHeight, "y is out of range");

  return heightmapData[y][x];
}

float Heightmap::getWidthPercentage(const Vec4& playerPosition) const {
  return (playerPosition.x - leftUp.x) / (rightDown.x - leftUp.x);
}

float Heightmap::getHeightPercentage(const Vec4& playerPosition) const {
  return (playerPosition.z - leftUp.z) / (rightDown.z - leftUp.z);
}