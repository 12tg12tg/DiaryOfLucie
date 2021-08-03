#pragma once
#define PI		3.141592654f
#define PI2		PI*2
#define PI_2	(PI/2) //90µµ
#define PI_4	(PI/4) //45µµ
#define PI_8	(PI/8) //22.5µµ
#define PI_16	(PI/16)

#define DEGREE(p) (PI/180)*(p)

namespace UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float x1, float y1, float x2, float y2);
	float RadianToDegree(float rad);
}