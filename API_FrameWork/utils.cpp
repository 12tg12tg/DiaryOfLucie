#include"framework.h"
#include "utils.h"

namespace UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);
		float angle = acos(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2; //360µµ ³ÑÀ¸¸é 360 »©¸éµÊ.
		}
		return angle;
	}
}
