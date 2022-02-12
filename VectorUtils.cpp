#include "VectorUtils.h"

bool VectorUtils::compareVec4(glm::vec4 vec1, glm::vec4 vec2)
{
  double epsilon = std::numeric_limits<float>::epsilon();
  vec1 = glm::abs(vec1);
  vec2 = glm::abs(vec2);

  //TODO Danger of substractive cancelation?
  glm::vec4 diffVec = glm::abs(vec1 - vec2);
  for(int i = 0; i < 4; i++)
  {
    if(diffVec[i] > epsilon)
    {
      return false;
    }
  }

  return true;
}