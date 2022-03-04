#ifndef _WIN32
/*
Workaround for some kind of linker bug. See https://bugs.launchpad.net/ubuntu/+source/nvidia-graphics-drivers-319/+bug/1248642
*/
#include <pthread.h>
void junk() {
  int i;
  i = pthread_getconcurrency();
};
#endif


#ifdef _WIN32
#include <windows.h>
#endif

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "Application.h"

#include <glm/vec2.hpp>

// Weak pointer to the application, so we can access it in callbacks
std::weak_ptr<Application> g_applicationPtr;


void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  int shouldClose = 0;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);

  if (key == GLFW_KEY_R && action == GLFW_PRESS)
    if (auto app = g_applicationPtr.lock())
      app->reloadScene();

  if (key == GLFW_KEY_C && action == GLFW_PRESS)
  {
    if (auto app = g_applicationPtr.lock())
    {
      std::cout << "Switch camera main" << std::endl;
      app->switchCamera();
    }
  }

  if (key == GLFW_KEY_V && action == GLFW_PRESS)
  {
    if (auto app = g_applicationPtr.lock())
    {
      std::cout << "Toggle shadows" << std::endl;
      app->toggleShadows();
    }
  }

}

void window_size_callback(GLFWwindow* window, int width, int height)
{
  if (auto app = g_applicationPtr.lock())
    app->setScreenSize(width, height);
}


GLFWwindow* initializeWindows(int width, int height)
{
  GLFWwindow* window = nullptr;

  // Initialize GLFW
  if (!glfwInit())
    return nullptr;

  window = glfwCreateWindow(width, height, "Lab1", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, keyboard_callback);

  glfwSetWindowSizeCallback(window, window_size_callback);


  // Initialize the "OpenGL Extension Wrangler" library
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    glfwTerminate();
    glfwDestroyWindow(window);

    return nullptr;
  }

  printf("GL version: %s\n", glGetString(GL_VERSION));
  printf("GL shading language version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

  return window;
}

void cleanupWindows(GLFWwindow *window)
{
  // Delete window before ending the program
  glfwDestroyWindow(window);
  // Terminate GLFW before ending the program
  glfwTerminate();
}


//Build geometry to add
std::shared_ptr<Transform> buildGeometryByHand()
{
  std::shared_ptr<Transform> cubeTransform = std::shared_ptr<Transform>(new Transform());
  cubeTransform->translate(glm::vec3(-150, -10, 250));
  cubeTransform->scale(glm::vec3(10, 10, 10));
  std::shared_ptr<Geometry> cube = std::shared_ptr<Geometry>(new Geometry());
  cubeTransform->addChild(cube);
  cube->resize(24);

  //Vertices.
  cube->insertVertex(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f), 0);
  cube->insertVertex(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f), 1);
  cube->insertVertex(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f), 2);
  cube->insertVertex(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 3);
  cube->insertVertex(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f), 4);
  cube->insertVertex(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 5);
  cube->insertVertex(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f), 6);
  cube->insertVertex(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f), 7);
  cube->insertVertex(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f), 8);
  cube->insertVertex(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f), 9);
  cube->insertVertex(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), 10);
  cube->insertVertex(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f), 11);
  cube->insertVertex(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), 12);
  cube->insertVertex(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f), 13);
  cube->insertVertex(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f), 14);
  cube->insertVertex(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f), 15);
  cube->insertVertex(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f), 16);
  cube->insertVertex(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f), 17);
  cube->insertVertex(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 18);
  cube->insertVertex(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f), 19);
  cube->insertVertex(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), 20);
  cube->insertVertex(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f), 21);
  cube->insertVertex(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f), 22);
  cube->insertVertex(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f), 23);

  //Normals.
  cube->insertNormal(glm::vec3(0.0f, 0.0f, 1.0f), 0);
  cube->insertNormal(glm::vec3(0.0f, 0.0f, 1.0f), 1);
  cube->insertNormal(glm::vec3(0.0f, 0.0f, 1.0f), 2);
  cube->insertNormal(glm::vec3(0.0f, 0.0f, 1.0f), 3);
  cube->insertNormal(glm::vec3(0.0f, 1.0f, 0.0f), 4);
  cube->insertNormal(glm::vec3(0.0f, 1.0f, 0.0f), 5);
  cube->insertNormal(glm::vec3(0.0f, 1.0f, 0.0f), 6);
  cube->insertNormal(glm::vec3(0.0f, 1.0f, 0.0f), 7);
  cube->insertNormal(glm::vec3(0.0f, 0.0f, -1.0f), 8);
  cube->insertNormal(glm::vec3(0.0f, 0.0f, -1.0f), 9);
  cube->insertNormal(glm::vec3(0.0f, 0.0f, -1.0f), 10);
  cube->insertNormal(glm::vec3(0.0f, 0.0f, -1.0f), 11);
  cube->insertNormal(glm::vec3(0.0f, -1.0f, 0.0f), 12);
  cube->insertNormal(glm::vec3(0.0f, -1.0f, 0.0f), 13);
  cube->insertNormal(glm::vec3(0.0f, -1.0f, 0.0f), 14);
  cube->insertNormal(glm::vec3(0.0f, -1.0f, 0.0f), 15);
  cube->insertNormal(glm::vec3(1.0f, 0.0f, 0.0f), 16);
  cube->insertNormal(glm::vec3(1.0f, 0.0f, 0.0f), 17);
  cube->insertNormal(glm::vec3(1.0f, 0.0f, 0.0f), 18);
  cube->insertNormal(glm::vec3(1.0f, 0.0f, 0.0f), 19);
  cube->insertNormal(glm::vec3(-1.0f, 0.0f, 0.0f), 20);
  cube->insertNormal(glm::vec3(-1.0f, 0.0f, 0.0f), 21);
  cube->insertNormal(glm::vec3(-1.0f, 0.0f, 0.0f), 22);
  cube->insertNormal(glm::vec3(-1.0f, 0.0f, 0.0f), 23);

  //Texture coordinates.
  cube->insertTexCoord(glm::vec2(0.695913f, -0.25f), 0);
  cube->insertTexCoord(glm::vec2(0.304087f, -0.25f), 1);
  cube->insertTexCoord(glm::vec2(0.695913f, 0.25f), 2);
  cube->insertTexCoord(glm::vec2(0.304087f, 0.25f), 3);
  cube->insertTexCoord(glm::vec2(0.695913f, 0.25f), 4);
  cube->insertTexCoord(glm::vec2(0.304087f, 0.25f), 5);
  cube->insertTexCoord(glm::vec2(0.695913f, -0.25f), 6);
  cube->insertTexCoord(glm::vec2(0.304087f, -0.25f), 7);
  cube->insertTexCoord(glm::vec2(0.695913f, -0.25f), 8);
  cube->insertTexCoord(glm::vec2(0.304087f, -0.25f), 9);
  cube->insertTexCoord(glm::vec2(0.695913f, 0.25f), 10);
  cube->insertTexCoord(glm::vec2(0.304087f, 0.25f), 11);
  cube->insertTexCoord(glm::vec2(0.695913f, 0.25f), 12);
  cube->insertTexCoord(glm::vec2(0.304087f, 0.25f), 13);
  cube->insertTexCoord(glm::vec2(0.695913f, -0.25f), 14);
  cube->insertTexCoord(glm::vec2(0.304087f, -0.25f), 15);
  cube->insertTexCoord(glm::vec2(0.304087f, -0.25f), 16);
  cube->insertTexCoord(glm::vec2(0.304087f, 0.25f), 17);
  cube->insertTexCoord(glm::vec2(0.304087f, 0.25f), 18);
  cube->insertTexCoord(glm::vec2(0.304087f, -0.25f), 19);
  cube->insertTexCoord(glm::vec2(0.695913f, 0.25f), 20);
  cube->insertTexCoord(glm::vec2(0.695913f, -0.25f), 21);
  cube->insertTexCoord(glm::vec2(0.695913f, -0.25f), 22);
  cube->insertTexCoord(glm::vec2(0.695913f, 0.25f), 23);

  //Indices.
  cube->insertElement(0);
  cube->insertElement(1);
  cube->insertElement(2);
  cube->insertElement(2);
  cube->insertElement(1);
  cube->insertElement(3);
  cube->insertElement(4);
  cube->insertElement(5);
  cube->insertElement(6);
  cube->insertElement(6);
  cube->insertElement(5);
  cube->insertElement(7);
  cube->insertElement(8);
  cube->insertElement(9);
  cube->insertElement(10);
  cube->insertElement(10);
  cube->insertElement(9);
  cube->insertElement(11);
  cube->insertElement(12);
  cube->insertElement(13);
  cube->insertElement(14);
  cube->insertElement(14);
  cube->insertElement(13);
  cube->insertElement(15);
  cube->insertElement(16);
  cube->insertElement(17);
  cube->insertElement(18);
  cube->insertElement(18);
  cube->insertElement(17);
  cube->insertElement(19);
  cube->insertElement(20);
  cube->insertElement(21);
  cube->insertElement(22);
  cube->insertElement(22);
  cube->insertElement(21);
  cube->insertElement(23);

  return cubeTransform;
}

int main(int argc, char** argv) 
{
  const unsigned SCREEN_WIDTH = 1920;
  const unsigned SCREEN_HEIGHT = 1080;

  GLFWwindow *window = initializeWindows(SCREEN_WIDTH, SCREEN_HEIGHT);

  std::shared_ptr<Application> application = std::make_shared<Application>(SCREEN_WIDTH, SCREEN_HEIGHT);
  g_applicationPtr = application;

  std::string model_filename = (char*) "Test";
  if (argc > 1)
    model_filename = argv[1];

  std::string v_shader_filename = "shaders/phong-shading.vert.glsl";
  std::string  f_shader_filename = "shaders/phong-shading.frag.glsl";

  if (argc < 2 ) {
    std::cerr << "Loading default model: " << model_filename << std::endl;
    std::cerr << "\n\nUsage: " << argv[0] << " <model-file>" << std::endl;
  }

  if (!application->initResources(model_filename, v_shader_filename, f_shader_filename))
  {
    cleanupWindows(window);
    return 1;
  }

  //std::shared_ptr<Transform> object = buildGeometryByHand();
  //application->add(object);

  application->initView();

  while (!glfwWindowShouldClose(window))
  {
    application->update(window);

    glfwSwapBuffers(window);
    glfwPollEvents();

    application->processInput(window);
  }

  cleanupWindows(window);

  return 0;
}

