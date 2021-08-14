#include "framework.h"
#include "moru.h"
#include "bulletManager.h"
moru::moru()
{
	IMAGE->addFrameImage("모루", "images/object/moru.bmp", 288, 384, 2, 4, true);
	BUTTON->addButton("모루-수리한다", 100, 100, 200, 40);
	BUTTON->buttonOn("모루-수리한다");
	BUTTON->addButton("모루-무시한다", 100, 100, 200, 40);
	BUTTON->buttonOn("모루-무시한다");
}

moru::~moru()
{
}

HRESULT moru::add(float centerx, float centery)
{
	_img = IMAGE->findImage("모루");
	_x = centerx - _img->getFrameWidth();
	_y = centery - _img->getFrameHeight();
	_hitRc = RectMake(_x + _img->getFrameWidth() / 9, _y + _img->getFrameHeight() / 4, 
		_img->getFrameWidth()*7/9, _img->getFrameHeight()*3/4);
	_footRc = RectMake(_hitRc.left, _hitRc.top + RecHeight(_hitRc) / 3, RecWidth(_hitRc), RecHeight(_hitRc) * 2 / 3);
	_interRc = RectMake(_footRc.left - RecWidth(PLAYER->getPlayerAddress().playerRect),
		_footRc.top - RecHeight(PLAYER->getPlayerAddress().playerRect),
		RecWidth(_footRc) + RecWidth(PLAYER->getPlayerAddress().playerRect)*2,
		RecHeight(_footRc) + RecHeight(PLAYER->getPlayerAddress().playerRect)*2);
	_state = MORUSTATE::NONE;
	int arr[] = { 0 };
	_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr)/sizeof(int), 5, true);
	_speakCount = 0;
	canInteraction = false;
	return S_OK;
}

void moru::release()
{
	BUTTON->removeButton("모루_수리한다");
	BUTTON->removeButton("모루_무시한다");
}

void moru::update(bulletManager* bm)
{
	bulletCollision(bm);
}

void moru::render()
{
	if (_isDebug) {
		ZORDER->ZorderRectangle(_interRc, ZFLOORMAP);
		ZORDER->ZorderRectangle(_hitRc, ZCOL1);
		ZORDER->ZorderRectangleColor(_footRc, ZCOL2, MINT);
	}
	ZORDER->ZorderAniRender(_img, ZUNIT, _footRc.bottom, _x, _y, _ani);

	//대화상자 출력
}

void moru::afterHit()
{

}

void moru::giveFrame()
{
	switch (_state)
	{
	case MORUSTATE::NONE:
		{
		int arr[] = { 0 };
		_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		break;
	case MORUSTATE::SPEAK:
		if (_speakCount == 0) {
			int arr[] = { 0, 1 };
			_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		break;
	case MORUSTATE::BROKEN:
		if (_speakCount == 0) {
			int arr[] = { 6, 3 };
			_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		break;
	case MORUSTATE::NOMONEY:
		if (_speakCount == 0) {
			int arr[] = { 0, 4 };
			_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		break;
	}
}

void moru::bulletCollision(bulletManager* bm)
{
	RECT temp;
	//1. 플레이어매직블릿
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &bm->getMgcBulInstance()->getVBullet()[i].rc, &_hitRc))
		{
			bm->getMgcBulInstance()->removeBullet(i);
		}
	}
	//2. 플레이어 화살
	for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++)
	{
		if (OBB->isOBBCollision(bm->getArwBulInstance()->getVBullet()[i].rc, bm->getArwBulInstance()->getVBullet()[i].angle, _hitRc, 0))
		{
			bm->getArwBulInstance()->removeBullet(i);
		}
	}
	//3. 검은 안해도 됨.
}

void moru::checkRepair()
{
	//충돌매니저에서 inter상자 충돌시 e키가 눌리면 canInteraction이 true가 됨.
	if (canInteraction)
	{
		//
		//수리를 할거냐는 문구와 버튼 두개가 뜸.
		



		//수리한다 선택시
		//돈 체크 후 
			//돈이 있으면 돈 차감 후 확률수리. 

				//성공시 speekCount = 0 으로 바꾸고 대화상자.
				
				//실패시 BROKEN상태로 바꾸고 대화상자.
			

			//돈이 없으면 NOMONEY 상태로 바꾸고 대화상자.



		//무시한다 선택시
			//NONE 상태로 돌아가기.





	}
}
