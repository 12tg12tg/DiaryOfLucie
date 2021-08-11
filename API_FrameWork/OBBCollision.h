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
	//�� ������ ������ ����ϴ� �Լ�. ������
	//(������) = x1*x2 + y1*y2
	double absDotVector(VECTOR a, VECTOR b) { //vector inner
		return abs(a.x * b.x + a.y * b.y);
	}

	//�λ簢���� �߽ɳ����� �Ÿ����͸� ���
	VECTOR getDistanceVector(SHAPE a, SHAPE b) {
		VECTOR ret;
		ret.x = (a.left + a.width / 2) - (b.left + b.width / 2);
		ret.y = (a.top + a.height / 2) - (b.top + b.height / 2);
		return ret;
	}

	//�簢���� ���̺��͸� ���
	VECTOR getHeightVector(SHAPE s) {
		VECTOR ret;
		ret.x = s.height * cosf(s.rot + PI_2) / 2;
		ret.y = - s.height * sinf(s.rot + PI_2) / 2;
		return ret;
	}

	//�簢���� �ʺ��͸� ���
	VECTOR getWidthVector(SHAPE s) {
		VECTOR ret;
		ret.x = s.width * cosf(s.rot) / 2;
		ret.y = - s.width * sinf(s.rot) / 2;
		return ret;
	}

	//�������� ������. ������
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
		//�簢�� ������ SHAPE����ü ���·� ����
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

		//�� �簢���� �߽ɳ����� �Ÿ����� ����صα�
		VECTOR dist = getDistanceVector(a, b);
		//�� �簢���� ���̿� �ʺ��� ���ݿ� �ش��ϴ� ���͸� ���ؼ� �迭�� ��´�.
		VECTOR vec[4] = { getHeightVector(a), getHeightVector(b), getWidthVector(a), getWidthVector(b) };
		//�׹����� ���͸� �ѹ��� �������� ��Ƽ�, ��� ������ ���翵�� �����Ѵ�(�������Ϳ��� ������ �̿��ϸ� �ȴ�)
		//�̶� ���翵�� ���Ǵ� ���ʹ� �ټ������̴�.
		//	1. �簢��1�� �������ݺ���
		//	2. �簢��1�� �ʺ����ݺ���
		//	3. �簢��2�� �������ݺ���
		//	4. �簢��2�� �ʺ����ݺ���
		//	5. �� �߽ɻ����� �Ÿ�����
		VECTOR unit;
		for (int i = 0; i < 4; i++) {
			double sum = 0;					//�� �װ��� ����/�ʺ� ������ ���翵���̰� ������ sum ����
			unit = getUnitVector(vec[i]);	//������ �����̵Ǵ� ����/�ʺ����� �������͸� ��� ����. �̰Ͱ� ���������ν� ���翵�� ���̸� ���� ���̴�.
			for (int j = 0; j < 4; j++) {
				sum += absDotVector(vec[j], unit);		//���ʴ�� �� ���� ���翵�� ���̸� ��� ���Ѵ�.
			}
			if (absDotVector(dist, unit) > sum) {		//���� �� ���翵�� ��� ���ߴµ�, �Ÿ������� ���翵�� ���̿� ����ģ�ٸ�, ����� �浹�� ���°� �ƴϴ�.
				return false;							//������ false ��ȯ.
			}
		}
		return true;									//�� ������ �����ϴ� ���߿� false�� ��ȯ���� �ʾҴٸ� �հ�. �浹�����̴�.
	}
};


