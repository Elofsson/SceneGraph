#include "FurGeometry.h"

FurGeometry::FurGeometry(int numLayers, float length, bool useVAO) : Geometry(useVAO)
{
  m_numLayers = numLayers;
  m_furLength = length;
}

bool FurGeometry::init(int seed, int density, int textureSlot)
{
  //Init texture here.
  return true;
}

void FurGeometry::apply(glm::mat4 transformMatrix)
{
  std::cout << "FurGeometry::apply" << std::endl;
}

void FurGeometry::draw()
{
  std::cout << "FurGeometry::draw" << std::endl;
}