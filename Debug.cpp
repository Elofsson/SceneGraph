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

