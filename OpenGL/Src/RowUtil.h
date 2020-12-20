#pragma once
#include "glm/glm.hpp"
#include <algorithm>

namespace rowUtil
{
	glm::vec3 RGBtoHSL(glm::vec3 rgb);
	glm::vec3 HSLtoRGB(glm::vec3 hsl);
	float hueToRGB(float p, float q, float t);
}