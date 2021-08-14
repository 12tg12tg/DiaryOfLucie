#include "framework.h"
#include "moru.h"
#include "bulletManager.h"
moru::moru()
{
	IMAGE->addFrameImage("모루", "images/object/moru.bmp", 288, 384, 2, 4, true);
	IMAGE->addImage("모루대화상자", "images/object/interactionBox.bmp", WINSIZEX*3/5, 200, false);
	but1 = BUTTON->addButton("모루-수리한다", 235, 568, 100, 30);
	but2 = BUTTON->addButton("모루-무시한다", 235, 600, 100, 30);
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
	_interRc = RectMake(_footRc.left - 1,//RecWidth(PLAYER->getPlayerAddress().playerRect),
		_footRc.top - 1,//RecHeight(PLAYER->getPlayerAddress().playerRect),
		RecWidth(_footRc) + 2,//RecWidth(PLAYER->getPlayerAddress().playerRect)*2,
		RecHeight(_footRc) + 2);//RecHeight(PLAYER->getPlayerAddress().playerRect)*2);
	_state = MORUSTATE::NONE;
	int arr[] = { 0 };
	_ani = ANIMATION->addNoneKeyAnimation("모루", arr, sizeof(arr)/sizeof(int), 5, true);
	_speakCount = 0;
	isConversation1 = false;
	isConversation2 = false;
	isConversation3 = false;
	isConversation4 = false;

	boxAlpha = 200;
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
	playerCollision();
	checkRepair();
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
	if (isConversation1)
	{
		//수리를 할거냐는 문구와 버튼 두개가 뜸.
		IMAGE->findImage("모루대화상자")->alphaRender(getMemDC(), WINSIZEX / 2 - IMAGE->findImage("모루대화상자")->getWidth() / 2,
			WINSIZEY - IMAGE->findImage("모루대화상자")->getHeight() - 75, 200);
		//지금 그 무기를 수리할텐가?
		//수리한다(30 골드)
		//무시한다
	}
	else if (isConversation2)
	{

	}
	else if (isConversation3)
	{

	}
	else if (isConversation4)
	{

	}

			//돈체크
			//if(돈 충분){
			//	
			//	if(수리 성공){
			//		speekCount = 0;
			//		자 수리가 완료되었네.
			//		돈차감
			//		isConversation1 = false;		//상호작용 종료.
			//	}
			//	else{
			//		speekCount = 0;
			//		_state = MORUSTATE::BROKEN;
			//		어이쿠 손이 미끄러졌네!
			//		가끔은 이런날도 있는게지..
			//		돈차감
			//		isConversation1 = false;		//상호작용 종료.
			//	}
			//}
			//else{
			//	speekCount = 0;
			//	_state = MORUSTATE::NOMONEY;
			//	자네는 돈이 부족해보이는구만.
			//	
			//	isConversation1 = false;		//상호작용 종료.
			//}
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

void moru::playerCollision()
{
	RECT temp;
	if (!isConversation1 && !isConversation2 && !isConversation3 && !isConversation4) {
		if (IntersectRect(&temp, &PLAYER->getPlayerAddress().playerRect, &_interRc))
		{
			if (PLAYER->getSTATEAddress() == STATE::IDLE && !isConversation1 && INPUT->isOnceKeyDown('E'))	//상호작용 버튼활성화
			{
				isConversation1 = true;
				BUTTON->buttonOn("모루-수리한다");
				BUTTON->buttonOn("모루-무시한다");
				_speakCount = 0;
				_state = MORUSTATE::SPEAK;
			}
		}
	}
}

void moru::checkRepair()
{
	_speakCount++;
	//충돌매니저에서 inter상자 충돌시 e키가 눌리면 canInteraction이 true가 됨.
	if (isConversation1)
	{
		//수리를 할거냐는 문구와 버튼 두개가 뜸.
		//지금 그 무기를 수리할텐가?
		//수리한다(30 골드)
		//무시한다


		//수리한다 선택시
		if (BUTTON->isClick("모루-수리한다")) {
			BUTTON->buttonOff("모루-수리한다");
			BUTTON->buttonOff("모루-무시한다");
			isConversation1 = false;
			if (true)//남은돈이충분하면)
			{
				//돈차감구문.
				if (true)//수리성공) 
				{
					_speakCount = 0;
					isConversation2 = true;	//자 수리가 완료되었네.
				}
				else
				{
					_speakCount = 0;
					_state = MORUSTATE::BROKEN;
					isConversation3 = true;	//어이쿠 손이 미끄러졌네.
				}
			}
			else {
				_speakCount = 0;
				_state = MORUSTATE::NOMONEY;
				isConversation4 = true;	//자네는 돈이 부족해보이는구만.
			}
		}
		//무시한다 선택시
		else if (BUTTON->isClick("모루-무시한다"))
		{
			BUTTON->buttonOff("모루-수리한다");
			BUTTON->buttonOff("모루-무시한다");
			_state = MORUSTATE::NONE;
			isConversation1 = false;
		}
	}
	if ((isConversation2 || isConversation3 || isConversation4) && (_speakCount > 100))
	{
		isConversation2 = false;
		isConversation3 = false;
		isConversation4 = false;
	}
}
