#include "framework.h"
#include "tack.h"

tack::tack()
{
	IMAGE->addImage("압정", "images/ponpoko/tack.bmp", 14, 14, true);
}

tack::~tack()
{
}

HRESULT tack::init(float x, float y)
{
	tagTack newTack;
	newTack.x = x;
	newTack.y = y;
	newTack.rc = RectMake(x + 6, y + 6, IMAGE->findImage("압정")->getWidth() - 12, IMAGE->findImage("압정")->getHeight() - 6);

	vTack.push_back(newTack);
	return S_OK;
}

void tack::release()
{
}

void tack::update()
{
}

void tack::render()
{
	for (viTack = vTack.begin(); viTack != vTack.end(); ++viTack)
	{
		IMAGE->render("압정", getMemDC(), viTack->x, viTack->y);
		if (isDebug) Rectangle(getMemDC(), viTack->rc.left, viTack->rc.top, viTack->rc.right, viTack->rc.bottom);
	}
}
