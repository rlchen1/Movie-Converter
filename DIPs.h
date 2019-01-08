#ifndef DIPS_H
#define DIPS_H

#include "Image.h"
#include "FileIO.h"

typedef enum
{
	HueRotateFilter,
	 SaturateFilter
}FilterType;

IMAGE *HueRotate(IMAGE *image, float angle);

IMAGE *Saturate(IMAGE *image, float percent);
#endif
