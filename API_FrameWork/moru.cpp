#include "framework.h"
#include "moru.h"
#include "bulletManager.h"
moru::moru()
{
	IMAGE->addFrameImage("���", "images/object/moru.bmp", 288, 384, 2, 4, true);
	IMAGE->addImage("�̸�����", "images/object/moruNamebox.bmp", 250, 52, false);
	IMAGE->addImage("����ȭ����", "images/object/interactionBox.bmp", WINSIZEX*3/5, 150, false);
	IMAGE->addImage("����̸�", "images/object/moruName.bmp", 225, 42, true);
	IMAGE->addImage("����Ʈ1", "images/object/morument1.bmp", 614, 160, true);
	IMAGE->addImage("����Ʈ2", "images/object/morument2.bmp", 614, 160, true);
	IMAGE->addImage("����Ʈ3", "images/object/morument3.bmp", 614, 160, true);
	IMAGE->addImage("����Ʈ4", "images/object/morument4.bmp", 614, 160, true);
	but1 = BUTTON->addButton("���-�����Ѵ�", 225, 475, 222, 35);
	but2 = BUTTON->addButton("���-�����Ѵ�", 225, 516, 222, 35);
	mouseoverImg = new image;
	mouseoverImg->init(222, 35, RGB(85, 115, 226));
}

moru::~moru()
{
}

HRESULT moru::add(float centerx, float centery)
{
	_img = IMAGE->findImage("���");
	_x = centerx - _img->getFrameWidth()/2;
	_y = centery - _img->getFrameHeight()/2;
	_hitRc = RectMake(_x + _img->getFrameWidth() / 9, _y + _img->getFrameHeight() / 4, 
		_img->getFrameWidth()*7/9, _img->getFrameHeight()*3/4);
	_footRc = RectMake(_hitRc.left, _hitRc.top + RecHeight(_hitRc) / 3, RecWidth(_hitRc), RecHeight(_hitRc) * 2 / 3);
	_interRc = RectMake(_footRc.left - 1,//RecWidth(PLAYER->getPlayerAddress().playerRect),
		_footRc.top - 1,//RecHeight(PLAYER->getPlayerAddress().playerRect),
		RecWidth(_footRc) + 2,//RecWidth(PLAYER->getPlayerAddress().playerRect)*2,
		RecHeight(_footRc) + 2);//RecHeight(PLAYER->getPlayerAddress().playerRect)*2);
	_state = MORUSTATE::NONE;
	int arr[] = { 0 };
	_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr)/sizeof(int), 5, true);
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
	BUTTON->removeButton("���_�����Ѵ�");
	BUTTON->removeButton("���_�����Ѵ�");
	SAFE_DELETE(mouseoverImg);
}

void moru::update(bulletManager* bm)
{
	bulletCollision(bm);
	playerCollision();
	giveFrame();
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

	//�ҹ� �����±�
	if (isConversation1 || isConversation2 || isConversation3 || isConversation4)
	{
		IMAGE->findImage("�̸�����")->alphaRender(getMemDC(), 188, 360, 200);
		IMAGE->findImage("����̸�")->render(getMemDC(), 200, 365);
		IMAGE->findImage("����ȭ����")->alphaRender(getMemDC(), WINSIZEX / 2 - IMAGE->findImage("����ȭ����")->getWidth() / 2,
			420, 200);
	}
	//��ȭ���� ���
	if (isConversation1)
	{
		//������ �ҰųĴ� ������ ��ư �ΰ��� ��.
		if (BUTTON->isMouseOver("���-�����Ѵ�")) {
			mouseoverImg->alphaRender(getMemDC(), 225, 475, 100);
		}										
		if (BUTTON->isMouseOver("���-�����Ѵ�")) {
			mouseoverImg->alphaRender(getMemDC(), 225, 516, 100);
		}
		IMAGE->findImage("����Ʈ1")->render(getMemDC(), 190, 410);
	}
	else if (isConversation2)
	{
		IMAGE->findImage("����Ʈ2")->render(getMemDC(), 190, 410);
	}
	else if (isConversation3)
	{
		IMAGE->findImage("����Ʈ3")->render(getMemDC(), 190, 410);
	}
	else if (isConversation4)
	{
		IMAGE->findImage("����Ʈ4")->render(getMemDC(), 190, 410);
	}
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
		ANIMATION->changeNonKeyAnimation(_ani, "���", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		break;
	case MORUSTATE::SPEAK:
		if (_speakCount == 0) {
			int arr[] = { 0, 1 };
			ANIMATION->changeNonKeyAnimation(_ani, "���", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			ANIMATION->changeNonKeyAnimation(_ani, "���", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		break;
	case MORUSTATE::BROKEN:
		if (_speakCount == 0) {
			int arr[] = { 6, 3 };
			ANIMATION->changeNonKeyAnimation(_ani, "���", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		else if (_speakCount == 120) {
			int arr[] = { 0 };
			ANIMATION->changeNonKeyAnimation(_ani, "���", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		break;
	case MORUSTATE::NOMONEY:
		if (_speakCount == 0) {
			int arr[] = { 0, 4 };
			ANIMATION->changeNonKeyAnimation(_ani, "���", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			ANIMATION->changeNonKeyAnimation(_ani, "���", arr, sizeof(arr) / sizeof(int), 6, true);
		}
		break;
	}
}

void moru::bulletCollision(bulletManager* bm)
{
	RECT temp;
	//1. �÷��̾������
	for (int i = 0; i < bm->getMgcBulInstance()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &bm->getMgcBulInstance()->getVBullet()[i].rc, &_hitRc))
		{
			bm->getMgcBulInstance()->removeBullet(i);
		}
	}
	//2. �÷��̾� ȭ��
	for (int i = 0; i < bm->getArwBulInstance()->getVBullet().size(); i++)
	{
		if (OBB->isOBBCollision(bm->getArwBulInstance()->getVBullet()[i].rc, bm->getArwBulInstance()->getVBullet()[i].angle, _hitRc, 0))
		{
			bm->getArwBulInstance()->removeBullet(i);
		}
	}
	//3. ���� ���ص� ��.
}

void moru::playerCollision()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getPlayerAddress().playerRect, &_footRc))
	{
		int fromtop, frombottom, fromleft, fromright;
		int centerx, centery;
		int min;
		centerx = temp.left + (temp.right - temp.left) / 2;
		centery = temp.top + (temp.bottom - temp.top) / 2;
		fromtop = centery - _footRc.top;
		frombottom = _footRc.bottom - centery;
		fromleft = centerx - _footRc.left;
		fromright = _footRc.right - centerx;

		min = (fromtop >= frombottom) ? frombottom : fromtop;
		min = (min >= fromleft) ? fromleft : min;
		min = (min >= fromright) ? fromright : min;
		if (min == fromtop && min <= 50)
		{
			PLAYER->getPlayerAddress().y = _footRc.top - (PLAYER->getPlayerAddress().playerRect.bottom - PLAYER->getPlayerAddress().playerRect.top) / 2;
		}
		else if (min == frombottom)
		{
			PLAYER->getPlayerAddress().y = _footRc.bottom + (PLAYER->getPlayerAddress().playerRect.bottom - PLAYER->getPlayerAddress().playerRect.top) / 2;
		}
		else if (min == fromleft)
		{
			PLAYER->getPlayerAddress().x = _footRc.left - (PLAYER->getPlayerAddress().playerRect.right - PLAYER->getPlayerAddress().playerRect.left) / 2;
		}
		else if (min == fromright)
		{
			PLAYER->getPlayerAddress().x = _footRc.right + (PLAYER->getPlayerAddress().playerRect.right - PLAYER->getPlayerAddress().playerRect.left) / 2;
		}
	}
	playerInterCollision();
}

void moru::playerInterCollision()
{
	RECT temp;
	if (!isConversation1 && !isConversation2 && !isConversation3 && !isConversation4) {
		if (IntersectRect(&temp, &PLAYER->getPlayerAddress().playerRect, &_interRc))
		{
			if (PLAYER->getSTATEAddress() == STATE::IDLE && !isConversation1 && INPUT->isOnceKeyDown('E'))	//��ȣ�ۿ� ��ưȰ��ȭ
			{
				isConversation1 = true;
				BUTTON->buttonOn("���-�����Ѵ�");
				BUTTON->buttonOn("���-�����Ѵ�");
				_speakCount = 0;
				_state = MORUSTATE::SPEAK;

				PLAYER->playerStop();
			}
		}
	}
}

void moru::checkRepair()
{
	_speakCount++;
	//�浹�Ŵ������� inter���� �浹�� eŰ�� ������ canInteraction�� true�� ��.
	if (isConversation1)
	{
		//�����Ѵ� ���ý�
		if (BUTTON->isClick("���-�����Ѵ�")) {
			BUTTON->buttonOff("���-�����Ѵ�");
			BUTTON->buttonOff("���-�����Ѵ�");
			isConversation1 = false;
			if (PLAYERDATA->changeGold(-30, true))//�� ��. ���� ����
			{
				PLAYERDATA->changeGold(-30, false);
				if (RND->getInt(2))
				{
					_speakCount = 0;
					isConversation2 = true;	//�� ������ �Ϸ�Ǿ���.
				}
				else
				{
					_speakCount = 0;
					_state = MORUSTATE::BROKEN;
					isConversation3 = true;	//������ ���� �̲�������.
				}
			}
			else {
				_speakCount = 0;
				_state = MORUSTATE::NOMONEY;
				isConversation4 = true;	//�ڳ״� ���� �����غ��̴±���.
			}
		}
		//�����Ѵ� ���ý�
		else if (BUTTON->isClick("���-�����Ѵ�"))
		{
			BUTTON->buttonOff("���-�����Ѵ�");
			BUTTON->buttonOff("���-�����Ѵ�");
			_state = MORUSTATE::NONE;
			isConversation1 = false;
			PLAYER->playerStop();
		}
	}
	if ((isConversation2 || isConversation4) && (_speakCount > 100))
	{
		isConversation2 = false;
		isConversation4 = false;
		PLAYER->playerStop();
	}
	if (isConversation3 && _speakCount > 120)
	{
		isConversation3 = false;
		PLAYER->playerStop();
	}
}
