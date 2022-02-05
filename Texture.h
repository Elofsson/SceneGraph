#pragma once

#include <vector>
#include <memory>

//TODO Should contain textures to be applied to surfaces.
//TODO Method to apply texture.

class Texture
{
  Texture();
};

typedef std::vector<std::shared_ptr<Texture>> TextureVector;