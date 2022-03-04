/**
 * @file Skybox.h
 * @author Elof Fahlstedt (dv19eft@cs.umu.se)
 * @brief Creates a skybox through a cubemap. Uses a 
 *        vector of 6 path images which will be the images
 *        used for the skybox. The vector should be in 
 *        the following order:
 * 
 *        1. Right.
 *        2. Left.
 *        3. Top
 *        4. Bottom
 *        5. Front
 *        6. Back
 *
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Texture.h"
#include "Loader.h"
#include "InitVisitor.h"
#include "RenderVisitor.h"


class SkyBox 
{    
private:
  std::shared_ptr<Texture> m_skyboxTexture;
  std::shared_ptr<Group> m_skyboxObject;
  std::shared_ptr<RenderVisitor> m_renderer;
  GLuint m_program;
  
  /**
   * @brief Initalize the skybox with the path to 
   *        the object that should be used as the 
   *        skybox. This obj file should probably
   *        be a cube.
   * 
   * @param objFilePath Path to obj file.
   */
  void initSkybox(const char *objFilePath);

  /**
   * @brief Create the cubemap texture from a vector
   *        of paths to the images to be used in the
   *        skybox. The order the images should be:
   *          
   *        1. Right.
   *        2. Left.
   *        3. Top
   *        4. Bottom
   *        5. Front
   *        6. Back
   * 
   * @param textures 
   * @return unsigned int 
   */
  void loadCubemap(std::vector<std::string> textures);

public:
  /**
   * @brief Construct a new Skybox object
   *        Creates a skybox from a vector
   *        of paths to the images to be used in the
   *        skybox and path to object file which
   *        will be used as skybox. This object should
   *        probably be a cube.
   *         The order the images should be:
   *          
   *        1. Right.
   *        2. Left.
   *        3. Top
   *        4. Bottom
   *        5. Front
   *        6. Back
   *
   * @param textures Textures to be used.
   * @param objFilePath Path to obj file
   */
  SkyBox(std::vector<std::string> textures, const char *objFilePath, GLuint skyboxProgram);
  ~SkyBox();

  /**
   * @brief Render the skybox.
   */
  void render();

  GLuint getProgram();

};