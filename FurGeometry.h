
#pragma once

#include "Geometry.h"
#include "Texture.h"

class FurGeometry : public Geometry
{
public:
  FurGeometry(int numLayers, float length, bool useVAO = true);
  bool init(int seed, int density, int textureSlot);
  void apply(glm::mat4 transformMatrix) override;
  void draw() override;

private:
  std::shared_ptr<Texture> m_furPatternTexture;
  int m_numLayers;
  float m_furLength;
};