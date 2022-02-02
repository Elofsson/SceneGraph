#pragma once
#include <GLFW/glfw3.h>

class FPSCounter
{
public:

  FPSCounter();
  void render(GLFWwindow* window);

private:
  void update();
    
  double m_lastTime;
  unsigned int m_numFrames;
  double m_fps;

};

