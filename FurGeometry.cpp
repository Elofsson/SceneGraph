#include "FurGeometry.h"

FurGeometry::FurGeometry(std::shared_ptr<Geometry> geometry, int numLayers, float length, bool useVAO) : Geometry(geometry, useVAO)
{
	m_numLayers = numLayers;
  m_furLength = length;
}

bool FurGeometry::init(int seed, int density, int size, int textureSlot)
{
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

	m_furPatternTexture->initData(width, height, textureSlot, GL_UNSIGNED_BYTE, GL_RGBA, data);
	free(data);

  return true;
}

bool FurGeometry::initShaders(GLuint program)
{

	if(!Geometry::initShaders(program))
	{
		std::cout << "Failed to load shaders for fur geometry" << std::endl;
		return false;
	}

	//TODO Should probably move somewhere else.
	//Apply texture.
	const char *uniform = "furPatternTexture";
	m_furPatternTexture->bind();
	m_furPatternTexture->apply(program, uniform);

	return true;
}

void FurGeometry::draw()
{
  std::cout << "FurGeometry::draw" << std::endl;

	float num = 1.0;
	float furMovement = 0.0;
	for(int i = 0; i < m_numLayers; i++)
	{	
		//Set current layer.
		glUniform1i(m_uniformCurrentLayer, i);

		//Set UV scale.
		num = num - (1 / m_numLayers);
		if(num > 1) num = 1;
		if(num < 0) num = 0;
		glUniform1i(m_uniformUVScale, num);

		//Fur movement
		furMovement += 0.0001;
		glUniform1f(m_uniformFurOffset, (furMovement * (i / m_numLayers)));

		//Draw the geometry.
		Geometry::draw();
	}
}