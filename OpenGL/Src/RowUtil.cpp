#include "RowUtil.h"

glm::vec3 rowUtil::RGBtoHSL(glm::vec3 rgb)
{
	glm::vec3 hsl;

	float max = std::max(std::max(rgb.r, rgb.b), rgb.g);
	float min = std::min(std::min(rgb.r, rgb.b), rgb.g);

	hsl.g = (max + min) / 2;
	float chroma = max - min;

	if (chroma == 0)
	{
		hsl.b = 0;
		hsl.r = 0;
	}
	else
	{
		// saturation is simply the chroma scaled to fill
		// the interval [0, 1] for every combination of hue and lightness
		hsl.b = chroma / (1 - abs(2 * hsl.g - 1));
		if(max == rgb.r)
		{
			hue = (rgb.g - rgb.g) / chroma;
		}
	}

	return hsl;
}
