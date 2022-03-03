#include "FurState.h"
#include "Geometry.h"


FurState::FurState(int numLayer, float furLength, float furOffset)
{
  m_furLength = furLength;
  m_numLayer = numLayer;
  m_furOffset = furOffset;
}

bool FurState::init(const char *furPattern, int width, int height)
{
  m_furPatternTexture = std::shared_ptr<Texture>(new Texture());
	bool res = m_furPatternTexture->init(furPattern, 5, GL_TEXTURE_2D, GL_UNSIGNED_BYTE);
  return true;
}

bool FurState::apply(Geometry &geometry, GLuint program)
{
  const char *uniformName = "currentLayer";
  m_uniformCurrentLayer = glGetUniformLocation(program, uniformName);
  if(m_uniformCurrentLayer == -1)
  {
    std::cout << "Failed to get uniform " << uniformName << std::endl;
    //return false;
  }

  uniformName = "furFlowOffset";
  m_uniformFurOffset = glGetUniformLocation(program, uniformName);
  if(m_uniformFurOffset == -1)
  {
    std::cout << "Failed to get uniform " << uniformName << std::endl;
    //return false;
  }

  uniformName = "furLength";
  m_uniformFurLength = glGetUniformLocation(program, uniformName);
  if(m_uniformFurLength == -1)
  {
    std::cout << "Failed to get uniform " << uniformName << std::endl;
    //return false;
  }

  //Draw the first layer without alpha.
  uniformName = "furPatternTexture";
	m_furPatternTexture->bind();
	m_furPatternTexture->apply(program, uniformName);
  setUniforms(0, m_furLength, 0.0);
  geometry.draw();

  //Enable alpha blending.
  glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //Draw the rest of the layers.
  float furOffset = m_furOffset;
  for(int layer = 1; layer < m_numLayer; layer++)
  {
    furOffset += m_furOffset;
    setUniforms(layer, m_furLength, furOffset);
    geometry.draw();
  }
  
  glDisable(GL_BLEND);
  
  return true;
}

void FurState::setUniforms(int layer, float furLength, float furOffset)
{
  //Set current layer.
  glUniform1i(m_uniformCurrentLayer, layer);

  //Set fur length.
  glUniform1f(m_uniformFurLength, m_furLength);

  //Set furoffset used for fur flow / movement.
  glUniform1f(m_uniformFurOffset, furOffset);
}

int FurState::getNumLayers()
{
  return m_numLayer;
}