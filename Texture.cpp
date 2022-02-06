#include "Texture.h"
#include <stb_image.h>
#include <vr/glErrorUtil.h>
#include <vr/FileSystem.h>

Texture::Texture()
{
}

bool Texture::init(const char *image, unsigned int slot, GLenum texType, GLenum pixelType)
{

  //Check if the image is valid
  std::string filepath = image;

	bool exist = vr::FileSystem::exists(filepath);

	std::string vrPath = vr::FileSystem::getEnv("VR_PATH");
	if (vrPath.empty())
		std::cerr << "The environment variable VR_PATH is not set. It should point to the directory where the vr library is (just above models)" << std::endl;

	if (!exist && !vrPath.empty())
	{
		filepath = std::string(vrPath) + "/" + filepath;
		exist = vr::FileSystem::exists(filepath);
	}
	if (!exist)
	{
		std::cerr << "Unable to locate image: " << image << std::endl;
		return false;
	}
  
  //Read the image.
  int widthImg, heightImg, numColCh;
  unsigned char *bytes = readTexture(filepath, &widthImg, &heightImg, &numColCh);
  if(!bytes)
  {
    std::cerr << "Error reading image: " << image << std::endl;
		return false;
  }

  GLenum texFormat = GL_RGBA;
  m_slot = slot;
  m_type = texType;


  if (numColCh == 3)
		texFormat = GL_RGB;

  //Generates an OpenGL texture object
	glGenTextures(1, &m_texture_id);

	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(texType, m_texture_id);

	CHECK_GL_ERROR_LINE_FILE();

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, texFormat, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);

  return true;
}

unsigned char* Texture::readTexture(std::string filePath, int *width, int *height, int *numChannels)
{
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(filePath.c_str(), width, height, numChannels, 0);
  return bytes;
}


//TODO check this apply method, looks wierd.
void Texture::apply(GLuint program)
{
  GLuint texUni = glGetUniformLocation(program, "material.textures");
  glUniform1i(texUni, m_slot);

  CHECK_GL_ERROR_LINE_FILE();

  texUni = glGetUniformLocation(program, "material.activeTextures");
  glUniform1i(texUni,(int) true);

  CHECK_GL_ERROR_LINE_FILE();

	glActiveTextureARB(GL_TEXTURE0 + m_slot);

	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	glBindTexture(m_type, m_texture_id);
}