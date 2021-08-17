#include "framework.h"
#include "progressBar.h"

progressBar::progressBar()
{
}

progressBar::~progressBar()
{
}

HRESULT progressBar::init(char* frontImage, char* backImage, float x, float y, int width, int height, bool isUi = true, bool isAlpha = false, BYTE alpha = 255)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);
	_progressBarFront = new image;
	_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));

	_progressBarBack = new image;
	_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarFront->getWidth();

	_isUi = isUi;

	_isAlpha = isAlpha;
	_alpha = alpha;

	return S_OK;
}

void progressBar::release()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar::render()
{
	if (_isUi) {
		if (!_isAlpha) {
			ZORDER->UIRender(_progressBarBack, ZUIFIRST, 0, _rcProgress.left, _y, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());
			ZORDER->UIRender(_progressBarFront, ZUISECOND, 0, _rcProgress.left, _y, 0, 0, _width, _progressBarBack->getHeight());
		}
		else {
			ZORDER->UIAlphaRender(_progressBarBack, ZUIFIRST, 0, _rcProgress.left, _y, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight(), _alpha);
			ZORDER->UIAlphaRender(_progressBarFront, ZUISECOND, 0, _rcProgress.left, _y, 0, 0, _width, _progressBarBack->getHeight(), _alpha);
		}
	}
	else {
		if (!_isAlpha) {
			ZORDER->ZorderRender(_progressBarBack, ZUNIT, 0, _rcProgress.left, _y, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());
			ZORDER->ZorderRender(_progressBarFront, ZUNIT, 0, _rcProgress.left, _y, 0, 0, _width, _progressBarBack->getHeight());
		}
		else {
			ZORDER->ZorderAlphaRender(_progressBarBack, ZUNIT, 0, _rcProgress.left, _y, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight(), _alpha);
			ZORDER->ZorderAlphaRender(_progressBarFront, ZUNIT, 0, _rcProgress.left, _y, 0, 0, _width, _progressBarBack->getHeight(), _alpha);
		}
	}
}

void progressBar::setGauge(float currentGauge, float maxGauge, BYTE alpha)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
	_alpha = alpha;
}
