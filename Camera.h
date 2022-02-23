#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

/// <summary>
/// Class that defines a Camera for OpenGL.
/// Handles keyboard events, handles Uniforms for view, projection and model matrix
/// </summary>
class Camera
{

public:

  /// <summary>
  /// Constructor
  /// </summary>
  Camera();

  /// <summary>
  /// Handle keyboard events
  /// </summary>
  /// <param name="window">The window for which keyboard events are handled</param>
  void processInput(GLFWwindow* window);

  /// <summary>
  /// Get the size of the window for this camera
  /// </summary>
  /// <returns>Return size of the window</returns>
  glm::uvec2 getScreenSize();

  /// <summary>
  /// Set the size of the window
  /// </summary>
  /// <param name="size">The new size</param>
  void setScreenSize(const glm::uvec2& size);

  /// <summary>
  /// Initialize the uniforms for the camera
  /// </summary>
  /// <param name="program">The active program for which uniforms should be registered</param>
  /// <returns></returns>
  bool init(GLuint program);

  /// <summary>
  /// Set the near/far distance of the projection volume
  /// </summary>
  /// <param name="nearFar">New near far</param>
  void setNearFar(const glm::vec2& nearFar);

  /// <summary>
  /// Set the horizontal field of view
  /// </summary>
  /// <param name="fov">The new fov</param>
  void setFov(float fov);

  /// <summary>
  /// Called when uniforms should be processed within the active program
  /// </summary>
  /// <param name="program"></param>
  void apply(GLuint program);

  /// <summary>
  /// Set the overall transform of the camera (position, up, direction)
  /// </summary>
  /// <param name="transform"></param>
  void setTransform(glm::mat4 transform);

  /// <summary>
  /// Set the position, direction and up vector of the camera
  /// </summary>
  /// <param name="eye">New position of the camera</param>
  /// <param name="direction">New direction</param>
  /// <param name="up">New up vector</param>
  void set(glm::vec3 eye, glm::vec3 direction, glm::vec3 up);

  /// <summary>
  /// Set the new position of the camera
  /// </summary>
  /// <param name="pos">New position</param>
  void setPosition(glm::vec3 pos);
  
  /// <summary>
  /// Get the position of the camera
  /// </summary>
  /// <returns>Current position of the camera</returns>
  glm::vec3 getPosition() const;

  /// <summary>
  /// Set an overall scaling factor for how fast the camera should move.
  /// Default is 1.0. For a large scene, camera might need to move faster.
  /// </summary>
  /// <param name="scale">New scaling factor for speed of the camera movement</param>
  void setSceneScale(float scale);

  glm::vec3 getDirection() const;

private:
  GLint m_uniform_v;
  GLint m_uniform_p;
  GLint m_uniform_v_inv;
  glm::uvec2 m_screenSize;
  glm::vec2 m_nearFar;

  glm::vec3 m_position;
  glm::vec3 m_direction;
  glm::vec3 m_up;

  // Prevents the camera from jumping around when first clicking left click
  bool m_firstClick;

  // Adjust the speed of the camera and it's sensitivity when looking around
  float m_speed;
  float m_sceneScale;
  float m_sensitivity;
  float m_fov;
};

