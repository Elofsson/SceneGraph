#pragma once

#include "Texture.h"
#include <cstdlib>
#include <iostream>

class FurState
{
public:
  FurState(int numLayer, int seed, float furLength);
  bool apply(GLuint program, int layer);
  int getNumLayers();
  

private:
  std::shared_ptr<Texture> m_furPatternTexture;
  int m_numLayer;
  float m_furLength;

  GLuint m_uniformCurrentLayer;
  GLuint m_uniformUVScale;
  GLuint m_uniformFurOffset;
  GLuint m_uniformFurLength;

};