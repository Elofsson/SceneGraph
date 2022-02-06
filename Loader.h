#pragma once

#include "Scene.h"
#include "Geometry.h"
#include "Group.h"
#include "Transform.h"
#include "Debug.h"
#include "Material.h"
#include "Texture.h"

/// Load a given file and add content to the scene
std::shared_ptr<Group> load3DModelFile(const std::string& filename);

// Load contents of an xml file into the scene
bool loadSceneFile(const std::string& xmlFile, std::shared_ptr<Scene>& scene);
