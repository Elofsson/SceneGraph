
#pragma once

#include "Geometry.h"
#include "Texture.h"

class FurGeometry : public Geometry
{
public:
  FurGeometry(std::shared_ptr<Geometry> geometry, int numLayers, float length, bool useVAO = true);
  bool init(int seed, int density, int size, int textureSlot);
  bool initShaders(GLuint program) override;
  void draw() override;

private:
  std::shared_ptr<Texture> m_furPatternTexture;
  int m_numLayers;
  float m_furLength;

  GLuint m_uniformCurrentLayer;
  GLuint m_uniformUVScale;
  GLuint m_uniformFurOffset;
  GLuint m_uniformFurLength;
};