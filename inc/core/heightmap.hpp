/*
# _____        ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licensed under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#pragma once

#include <tyra>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "core/tinyphysicsengine.hpp"
#include "core/helper.hpp"

using Tyra::Vec4;

class Heightmap {
 public:
  Heightmap(const float& minHeight, const float& maxHeight, const Vec4& leftUp,
            const Vec4& rightDown);
  ~Heightmap();

  float getHeightOffset(const Vec4& playerPosition) const;

  bool isOutside(const Vec4& position) const;

  s16 mapWidth, mapHeight;
  float minHeight, maxHeight;
  Vec4 leftUp, rightDown;

 private:
    std::vector<std::vector<float>> heightmapData;
  float getWidthPercentage(const Vec4& playerPosition) const;
  float getHeightPercentage(const Vec4& playerPosition) const;
  float getGameHeight(const u8& inputColor, const u8& minColor,
                      const u8& maxColor) const;
};
