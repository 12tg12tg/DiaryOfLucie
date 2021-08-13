#include "framework.h"
#include "effect.h"

effect::effect() : 
	_effectImage(nullptr),
	_effectAni(nullptr), 
	_isRunning(NULL),
	_x(0),
	_y(0),
	_alpha(255)
{
}

effect::~effect()
{
}

HRESULT effect::init(image* effectImage, float z, int frameW, int frameH, int FPS, float elapsedTime, BYTE alpha)
{
	//이펙트 이미지가 없을 때 리턴
	if (!effectImage) return E_FAIL;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_isRunning = false;
	//이펙트 애니메이션이 없으면, 새로만들기
	if (!_effectAni) _effectAni = new animation;

	_frameW = frameW;
	_frameH = frameH;
	_z = z;
	_effectAni->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAni->setDefPlayFrame();
	_effectAni->setFPS(FPS);
	_alpha = alpha;

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
	//이펙트 애니메이션이 종료가 되면 멈추자.
	if (!_effectAni->isPlay()) stopEffect();
}

void effect::render()
{
	if (_isRunning)
	{
		//투명값이 없으면 그냥 랜더
		if (_alpha == 255) {
			ZORDER->ZorderAniRender(_effectImage, _z, _y + _frameH, _x, _y, _effectAni);
		}
		//투명값이 초기화되있으면 알파랜더
		else {
			ZORDER->ZorderAniAlphaRender(_effectImage, _z, _y + _frameH, _x, _y, _effectAni, _alpha);
		}
	}
}

void effect::startEffect(int x, int y)
{
	//위치 좌표를 센터 좌표로 만들기
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();

}

void effect::stopEffect()
{
	_isRunning = false;
}
