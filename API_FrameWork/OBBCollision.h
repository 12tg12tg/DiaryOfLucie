#pragma once
#include"gameNode.h"

struct VECTOR {
	double x, y;
};

struct SHAPE { //define shape
	double top, left, height, width, rot;
};

class OBBCollision
{
	VECTOR addVector(VECTOR a, VECTOR b)//vector plus
	{
		VECTOR ret;
		ret.x = a.x + b.x;
		ret.y = a.y + b.y;
		return ret;
	}
	double absDotVector(VECTOR a, VECTOR b) { //vector inner
		return abs(a.x * b.x + a.y * b.y);
	}
	double Deg2Rad(double deg) { //deg -> rad
		return deg / 180 * 3.141592;
	}
	VECTOR getDistanceVector(SHAPE a, SHAPE b) { //distance vector
		VECTOR ret;
		ret.x = (a.left + a.width / 2) - (b.left + b.width / 2);
		ret.y = (a.top + a.height / 2) - (b.top + b.height / 2);
		return ret;
	}

	VECTOR getHeightVector(SHAPE a) { //height vector
		VECTOR ret;
		ret.x = a.height * cos(Deg2Rad(a.rot - 90)) / 2;
		ret.y = a.height * sin(Deg2Rad(a.rot - 90)) / 2;
		return ret;
	}

	VECTOR getWidthVector(SHAPE a) { //width vector
		VECTOR ret;
		ret.x = a.width * cos(Deg2Rad(a.rot)) / 2;
		ret.y = a.width * sin(Deg2Rad(a.rot)) / 2;
		return ret;
	}

	VECTOR getUnitVector(VECTOR a) { //unit vector
		VECTOR ret;
		double size;
		size = sqrt(pow(a.x, 2) + pow(a.y, 2));
		ret.x = a.x / size;
		ret.y = a.y / size;
		return ret;
	}
public:
	bool OBB(SHAPE a, SHAPE b);
	
};

