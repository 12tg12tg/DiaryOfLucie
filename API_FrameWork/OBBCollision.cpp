#include "framework.h"
#include "OBBCollision.h"

bool OBBCollision::OBB(SHAPE a, SHAPE b)
{
	VECTOR dist = getDistanceVector(a, b);
	VECTOR vec[4] = { getHeightVector(a), getHeightVector(b), getWidthVector(a), getWidthVector(b) };
	VECTOR unit;
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		unit = getUnitVector(vec[i]);
		for (int j = 0; j < 4; j++) {
			sum += absDotVector(vec[j], unit);
		}
		if (absDotVector(dist, unit) > sum) {
			return false;
		}
	}
	return true;
}
