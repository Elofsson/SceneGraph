#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "Material.h"

/**
 * @brief Simple debug class used to debug
 *        matrices, vectors and materials.
 * 
 */
class Debug
{
public:
  static void printMat4(glm::mat4 mat);
  static void printMat4(const char *message, glm::mat4 mat);
  static void printVec4(glm::vec4 vec);
  static void printVec4(const char *message, glm::vec4 vec);
  static void printMaterial(std::shared_ptr<Material> material);

private:
  Debug(){}
};