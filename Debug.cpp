#include "Debug.h"

void Debug::printMat4(glm::mat4 mat)
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      std::cout << " " << mat[i][j];
    }
    std::cout << std::endl;
  }
}

void Debug::printMat4(const char *message, glm::mat4 mat)
{
  std::cout << message << std::endl;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      std::cout << " " << mat[i][j];
    }
    std::cout << std::endl;
  }
}

void Debug::printVec4(glm::vec4 vec)
{
  for(int i = 0; i < 4; i++)
  {
    std::cout << " " << vec[i];
  }
  std::cout << std::endl; 
}

void Debug::printVec4(const char *message, glm::vec4 vec)
{
  std::cout << message << std::endl;
  for(int i = 0; i < 4; i++)
  {
    std::cout << " " << vec[i];
  } 
  std::cout << std::endl;
}

 void Debug::printMaterial(std::shared_ptr<Material> material)
 {
  if(!material)
  {
    std::cout << "Material is null" << std::endl;
    return;
  }
  std::cout << "Material: " << std::endl;
  printVec4("Ambient ", material->getAmbient());
  printVec4("Diffuse ", material->getDiffuse());
  printVec4("Specular ", material->getSpecular());
  std::cout << "Shininess " << material->getShininess() << std::endl;
 }

