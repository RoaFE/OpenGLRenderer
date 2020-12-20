#include "RowUtil.h"

glm::vec3 rowUtil::RGBtoHSL(glm::vec3 rgb)
{

	glm::vec3 hsl;
	float max = std::max(std::max(rgb.r, rgb.b), rgb.g);
	float min = std::min(std::min(rgb.r, rgb.b), rgb.g);

	hsl.b = (max + min) / 2;
	float chroma = max - min;

	if (chroma == 0)
	{
		hsl.g = 0;
		hsl.r = 0;
	}
	else
	{
		// saturation is simply the chroma scaled to fill
		// the interval [0, 1] for every combination of hue and lightness
		hsl.g = hsl.b > 0.5 ? chroma / (2 - max - min) : chroma / (max + min);
		if(max == rgb.r)
		{
			hsl.r = ((rgb.g - rgb.b) / chroma) + (rgb.g < rgb.b ? 6 : 0);
		}
		else if (max == rgb.g)
		{
			hsl.r = ((rgb.b - rgb.r) / chroma )+ 2;
		}
		else if (max == rgb.b)
		{
			hsl.r = ((rgb.r - rgb.g) / chroma) + 4;
		}
		hsl.r /= 6;
		//hsl.g = chroma / (1 - abs(2 * hsl.g - 1));
	}

	return hsl;
}

glm::vec3 rowUtil::HSLtoRGB(glm::vec3 hsl)
{
	glm::vec3 rgb;
	if (hsl.g == 0)
	{
		rgb.r = rgb.b = rgb.g = hsl.b;
	}
	else
	{
		float q = hsl.b < 0.5 ? hsl.b * (1 + hsl.g) : hsl.b + hsl.g - (hsl.b * hsl.g);
		float p = 2 * hsl.b - q;
		rgb.r = hueToRGB(p, q, hsl.r + 1.f / 3.f);
		rgb.g = hueToRGB(p, q, hsl.r);
		rgb.b = hueToRGB(p, q, hsl.r - 1.f / 3.f);
	}
	return rgb;
}

float rowUtil::hueToRGB(float p, float q, float t)
{
	if (t < 0)
		t += 1;
	if (t > 1)
		t -= 1;
	if (t < 1.f / 6.f)
		return p + (q - p) * 6 * t;
	if (t < 1.f / 2.f)
		return q;
	if (t < 2.f / 3.f) 
		return p + (q - p) * (2.f / 3.f - t) * 6;
	return p;
}
