#pragma once
#define PI		3.141592654f //180도
#define PI2		PI*2 //360도
#define PI_2	(PI/2) //90도
#define PI_4	(PI/4) //45도
#define PI_8	(PI/8) //22.5도
#define PI_16	(PI/16)

#define DEGREE(p) (PI/180)*(p)
#define RADIAN(p) (180/PI)*(p)

#define UPLEFTANGLE (3*PI/4)
#define UPANGLE (PI/2)
#define UPRIGHTANGLE (PI/4)
#define RIHGTANGLE 0
#define DOWNRIGHTANGLE (7*PI/4)
#define DOWNANGLE (3*PI/2)
#define DOWNLEFTANGLE (5*PI/4)
#define LEFTANGLE PI

namespace UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float x1, float y1, float x2, float y2);
	float RadianToDegree(float rad);
}