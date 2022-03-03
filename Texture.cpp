#include "Texture.h"
#include <stb_image.h>
#include <vr/glErrorUtil.h>
#include <vr/FileSystem.h>

Texture::Texture()
{
}

bool Texture::init(const char *image, unsigned int slot, GLenum texType, GLenum pixelType)
{

	//Get texture path.
	std::string filePath = getFilePath(image);
	if(filePath.empty())
	{
		return false;
	}
  
  //Read the image.
  int widthImg, heightImg, numColCh;
  unsigned char *bytes = readTexture(filePath, &widthImg, &heightImg, &numColCh);
  if(!bytes)
  {
    std::cerr << "Error reading image: " << image << std::endl;
		return false;
  }

	//Setup texture attributes.
  m_slot = slot;
  m_type = texType;

	GLenum texFormat = GL_RGBA;
  if (numColCh == 3)
		texFormat = GL_RGB;

	setupTexture();

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, texFormat, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(m_type, 0);
  return true;
}

void Texture::initEmpty(unsigned int width, unsigned int height, unsigned int slot, GLenum texType, GLenum pixelType)
{
	//Setup texture attributes.
  m_slot = slot;
  m_type = texType;

	setupTexture();

  setWrapSetting(GL_CLAMP_TO_EDGE);
	setFilterSetting(GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, pixelType, 0);

	glGenerateMipmap(texType);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(m_type, 0);
}

void Texture::initData(unsigned int width, unsigned int height, unsigned int slot, GLenum texType, GLenum pixelType, GLubyte *data)
{
	//Setup texture attributes.
  m_slot = slot;
  m_type = texType;

	setupTexture();

  setWrapSetting(GL_CLAMP_TO_EDGE);
	setFilterSetting(GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Assigns the image to the OpenGL Texture object
	glTexStorage2D(GL_TEXTURE_2D, slot, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(m_type, 0);
}

bool Texture::initCubemap(std::vector<std::string> textures, unsigned int slot, GLenum texType, GLenum pixelType)
{
	//Setup texture attributes with defaults.
  m_slot = slot;
  m_type = texType;
	setupTexture();

	for(int i = 0; i < textures.size(); i++)
	{	
		//Validate image.
		std::string filePath = getFilePath(textures[i].c_str());
		if(filePath.empty())
		{
			return false;
		}

		//Default format
		GLenum texFormat = GL_RGBA;

		//Read the image.
		int widthImg, heightImg, numColCh;
		unsigned char *bytes = readTexture(filePath, &widthImg, &heightImg, &numColCh, false);
		if(!bytes)
		{
			std::cerr << "Error reading image: " << filePath << std::endl;
			return false;
		}

		//Update format depending on the type of image.
		if (numColCh == 3)
			texFormat = GL_RGB;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                    0, GL_RGBA, widthImg, heightImg, 0, texFormat, pixelType, bytes);

		stbi_image_free(bytes);
	}

	//Update filter and wrap settings.
	setFilterSetting(GL_LINEAR);
	setWrapSetting(GL_CLAMP_TO_EDGE);

	glBindTexture(m_type, 0);
	return true;
}

//NOTE Call unbind after this is called.
void Texture::setupTexture()
{
	//Generates an OpenGL texture object
	glGenTextures(1, &m_texture_id);

	// Assigns the texture to a Texture Unit
	glActiveTextureARB(GL_TEXTURE0 + m_slot);
	glBindTexture(m_type, m_texture_id);

	CHECK_GL_ERROR_LINE_FILE();

	// Configures the type of algorithm that is used to make the image smaller or bigger
	setFilterSetting(GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	setWrapSetting(GL_REPEAT);
}

std::string Texture::getFilePath(const char *image)
{
	//Check if the image is valid
	std::string empty = "";
  std::string filepath = image;

	bool exist = vr::FileSystem::exists(filepath);

	std::string vrPath = vr::FileSystem::getEnv("VR_PATH");
	if (vrPath.empty())
	{
		std::cerr << "The environment variable VR_PATH is not set. It should point to the directory where the vr library is (just above models)" << std::endl;
		return empty;
	}

	if (!exist && !vrPath.empty())
	{
		filepath = std::string(vrPath) + "/" + filepath;
		exist = vr::FileSystem::exists(filepath);
	}
	if (!exist)
	{
		std::cerr << "Unable to locate image: " << image << std::endl;
		return empty;
	}

	return filepath;
}

void Texture::setWrapSetting(GLuint wrapSetting)
{
	glTexParameteri(m_type, GL_TEXTURE_WRAP_S, wrapSetting);
	glTexParameteri(m_type, GL_TEXTURE_WRAP_T, wrapSetting);
	//glTexParameteri(m_type, GL_TEXUTRE_WRAP_R, wrapSetting);
}

void Texture::setFilterSetting(GLuint filterSetting)
{
	glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, filterSetting);
	glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, filterSetting);
}

unsigned char* Texture::readTexture(std::string filePath, int *width, int *height, int *numChannels, bool flip)
{
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(flip);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(filePath.c_str(), width, height, numChannels, 0);
  return bytes;
}


//TODO check this apply method, looks wierd.
void Texture::apply(GLuint program, std::string uniform)
{

  bind();

  GLuint texUni = glGetUniformLocation(program, uniform.c_str());
  glUniform1i(texUni, m_slot);

  CHECK_GL_ERROR_LINE_FILE();
}

void Texture::bind()
{
	glActiveTextureARB(GL_TEXTURE0 + m_slot);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(m_type, m_texture_id);
}

void Texture::unbind()
{
	glBindTexture(m_type, m_texture_id);
}

//TODO find another solution to this.
GLuint Texture::getTextureId()
{
	return m_texture_id;
}