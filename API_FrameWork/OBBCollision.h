#pragma once
#include "singleton.h"
struct VECTOR {
	double x, y;
};

struct SHAPE {
	double top, left, height, width, rot;
};

class OBBCollision : public Singleton<OBBCollision>
{
private:
	//두 벡터의 내적을 계산하는 함수. 공식은
	//(내적값) = x1*x2 + y1*y2
	double absDotVector(VECTOR a, VECTOR b) { //vector inner
		return abs(a.x * b.x + a.y * b.y);
	}

	//두사각형의 중심끼리의 거리벡터를 계산
	VECTOR getDistanceVector(SHAPE a, SHAPE b) {
		VECTOR ret;
		ret.x = (a.left + a.width / 2) - (b.left + b.width / 2);
		ret.y = (a.top + a.height / 2) - (b.top + b.height / 2);
		return ret;
	}

	//사각형의 높이벡터를 계산
	VECTOR getHeightVector(SHAPE s) {
		VECTOR ret;
		ret.x = s.height * cosf(s.rot + PI_2) / 2;
		ret.y = - s.height * sinf(s.rot + PI_2) / 2;
		return ret;
	}

	//사각형의 너비벡터를 계산
	VECTOR getWidthVector(SHAPE s) {
		VECTOR ret;
		ret.x = s.width * cosf(s.rot) / 2;
		ret.y = - s.width * sinf(s.rot) / 2;
		return ret;
	}

	//단위벡터 얻어오기. 공식은
	//x = x / size
	//y = y / size
	VECTOR getUnitVector(VECTOR a) {
		VECTOR ret;
		double size;
		size = sqrt(pow(a.x, 2) + pow(a.y, 2));
		ret.x = a.x / size;
		ret.y = a.y / size;
		return ret;
	}
public:
	bool OBBCollision::isOBBCollision(RECT rc1, float radian1, RECT rc2, float radian2)
	{
		//사각형 정보를 SHAPE구조체 형태로 변경
		SHAPE a, b;
		a.top = rc1.top;
		a.left = rc1.left;
		a.width = (double)(rc1.right - rc1.left);
		a.height = (double)(rc1.bottom - rc1.top);
		a.rot = radian1;

		b.top = rc2.top;
		b.left = rc2.left;
		b.width = (double)(rc2.right - rc2.left);
		b.height = (double)(rc2.bottom - rc2.top);
		b.rot = radian2;

		//두 사각형의 중심끼리의 거리벡터 계산해두기
		VECTOR dist = getDistanceVector(a, b);
		//두 사각형의 높이와 너비의 절반에 해당하는 벡터를 구해서 배열에 담는다.
		VECTOR vec[4] = { getHeightVector(a), getHeightVector(b), getWidthVector(a), getWidthVector(b) };
		//네방향의 벡터를 한번씩 기준으로 삼아서, 모든 벡터의 정사영을 투영한다(단위벡터와의 내적을 이용하면 된다)
		//이때 정사영이 계산되는 벡터는 다섯가지이다.
		//	1. 사각형1의 높이절반벡터
		//	2. 사각형1의 너비절반벡터
		//	3. 사각형2의 높이절반벡터
		//	4. 사각형2의 너비절반벡터
		//	5. 두 중심사이의 거리벡터
		VECTOR unit;
		for (int i = 0; i < 4; i++) {
			double sum = 0;					//총 네개의 높이/너비 벡터의 정사영길이가 합쳐질 sum 변수
			unit = getUnitVector(vec[i]);	//현재의 기준이되는 높이/너비벡터의 단위벡터를 담는 변수. 이것과 내적함으로써 정사영의 길이를 얻을 것이다.
			for (int j = 0; j < 4; j++) {
				sum += absDotVector(vec[j], unit);		//차례대로 네 개의 정사영의 길이를 모두 더한다.
			}
			if (absDotVector(dist, unit) > sum) {		//만약 네 정사영을 모두 더했는데, 거리벡터의 정사영의 길이에 못미친다면, 절대로 충돌한 상태가 아니다.
				return false;							//때문에 false 반환.
			}
		}
		return true;									//위 과정을 진행하는 도중에 false로 반환되지 않았다면 합격. 충돌상태이다.
	}
};


