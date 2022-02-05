#pragma once

#include <glm/glm.hpp>
#include <iostream>

class Debug
{
public:
  static void printMat4(glm::mat4 mat);
  static void printMat4(const char *message, glm::mat4 mat);

private:
  Debug(){}
};