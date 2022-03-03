#pragma once

#include "Texture.h"
#include <cstdlib>
#include <iostream>

class Geometry;

class FurState
{
public:
  FurState(int numLayer, float furLength, float furOffset);
  bool init(const char *furPattern, int width, int height);
  bool apply(Geometry &geometry, GLuint program);
  int getNumLayers();

private:

  void setUniforms(int layer, float furLength, float furOffset);

  std::shared_ptr<Texture> m_furPatternTexture;
  int m_numLayer;
  float m_furLength;
  float m_furOffset;

  GLuint m_uniformCurrentLayer;
  GLuint m_uniformUVScale;
  GLuint m_uniformFurOffset;
  GLuint m_uniformFurLength;

};