#include "FurState.h"


FurState::FurState(int numLayer, int seed, float furLength)
{
  m_furLength = furLength;
  m_numLayer = numLayer;

  //TODO pass as parameters maybe?
  int width = 1920;
  int height = 1080;

  //Initalzie data.

  //Simple method to generate a random noise.
	srand(seed);
	unsigned char *data = (unsigned char *) calloc(width * height, sizeof(unsigned char));
	for(int row = 0; row < height; row++)
	{
		for(int col = 0; col < width; col++)
		{
			data[row * height + col] = (rand() % 32768) / 32768.0;
		}
	}

  //TODO find a way to set a good slot.
  m_furPatternTexture = std::shared_ptr<Texture>(new Texture());
	m_furPatternTexture->initData(width, height, 5, GL_UNSIGNED_BYTE, GL_RGBA, data);
	free(data);
}

bool FurState::apply(GLuint program, int layer)
{
  const char *uniformName = "currentLayer";
  m_uniformCurrentLayer = glGetUniformLocation(program, uniformName);
  if(m_uniformCurrentLayer == -1)
  {
    std::cout << "Failed to get uniform " << uniformName << std::endl;
    return false;
  }

  uniformName = "furFlowOffset";
  m_uniformFurOffset = glGetUniformLocation(program, uniformName);
  if(m_uniformFurOffset == -1)
  {
    std::cout << "Failed to get uniform " << uniformName << std::endl;
    return false;
  }

  uniformName = "furLength";
  m_uniformFurLength = glGetUniformLocation(program, uniformName);
  if(m_uniformFurLength == -1)
  {
    std::cout << "Failed to get uniform " << uniformName << std::endl;
    return false;
  }

  uniformName = "UVScale";
  m_uniformUVScale = glGetUniformLocation(program, uniformName);
  if(m_uniformUVScale == -1)
  {
    std::cout << "Failed to get uniform " << uniformName << std::endl;
    //return false;
  }

  uniformName = "furPatternTexture";
	m_furPatternTexture->bind();
	m_furPatternTexture->apply(program, uniformName);

  //Set current layer.
  glUniform1i(m_uniformCurrentLayer, layer);

  //Set UV scale.
  float num = 1.0f;
  num = num - (1 / m_numLayer);
  if(num > 1) num = 1;
  if(num < 0) num = 0;
  glUniform1i(m_uniformUVScale, num);

  //TODO add movement
  //Fur movement
  //furMovement += 0.0001;
  //glUniform1f(m_uniformFurOffset, (furMovement * (i / m_numLayers)));


  return true;
}

int FurState::getNumLayers()
{
  return m_numLayer;
}