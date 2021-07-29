#include "framework.h"
#include "effect.h"

effect::effect() : 
	_effectImage(nullptr),
	_effectAni(nullptr), 
	_isRunning(NULL),
	_x(0),
	_y(0)
{
}

effect::~effect()
{
}

HRESULT effect::init(image* effectImage, int frameW, int frameH, int FPS, float elapsedTime)
{
	//����Ʈ �̹����� ���� �� ����
	if (!effectImage) return E_FAIL;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_isRunning = false;
	//����Ʈ �ִϸ��̼��� ������, ���θ����
	if (!_effectAni) _effectAni = new animation;

	_effectAni->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAni->setDefPlayFrame();
	_effectAni->setFPS(FPS);


	return S_OK;
}

void effect::release()
{
	SAFE_DELETE(_effectAni);
}

void effect::update()
{
	if (_isRunning)
	{
		_effectAni->frameUpdate(_elapsedTime);
	}
	//����Ʈ �ִϸ��̼��� ���ᰡ �Ǹ� ������.
	if (!_effectAni->isPlay()) stopEffect();
}

void effect::render()
{
	if (_isRunning)
	{
		_effectImage->aniRender(getMemDC(), _x, _y, _effectAni);
	}
}

void effect::startEffect(int x, int y)
{
	//��ġ ��ǥ�� ���� ��ǥ�� �����
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();

}

void effect::stopEffect()
{
	_isRunning = false;
}
