#include "framework.h"
#include "moru.h"
#include "bulletManager.h"
moru::moru()
{
	IMAGE->addFrameImage("���", "images/object/moru.bmp", 288, 384, 2, 4, true);
	IMAGE->addImage("����ȭ����", "images/object/interactionBox.bmp", WINSIZEX*3/5, 200, false);
	but1 = BUTTON->addButton("���-�����Ѵ�", 235, 568, 100, 30);
	but2 = BUTTON->addButton("���-�����Ѵ�", 235, 600, 100, 30);
}

moru::~moru()
{
}

HRESULT moru::add(float centerx, float centery)
{
	_img = IMAGE->findImage("���");
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

	//��ȭ���� ���
	if (isConversation1)
	{
		//������ �ҰųĴ� ������ ��ư �ΰ��� ��.
		IMAGE->findImage("����ȭ����")->alphaRender(getMemDC(), WINSIZEX / 2 - IMAGE->findImage("����ȭ����")->getWidth() / 2,
			WINSIZEY - IMAGE->findImage("����ȭ����")->getHeight() - 75, 200);
		//���� �� ���⸦ �������ٰ�?
		//�����Ѵ�(30 ���)
		//�����Ѵ�
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

			//��üũ
			//if(�� ���){
			//	
			//	if(���� ����){
			//		speekCount = 0;
			//		�� ������ �Ϸ�Ǿ���.
			//		������
			//		isConversation1 = false;		//��ȣ�ۿ� ����.
			//	}
			//	else{
			//		speekCount = 0;
			//		_state = MORUSTATE::BROKEN;
			//		������ ���� �̲�������!
			//		������ �̷����� �ִ°���..
			//		������
			//		isConversation1 = false;		//��ȣ�ۿ� ����.
			//	}
			//}
			//else{
			//	speekCount = 0;
			//	_state = MORUSTATE::NOMONEY;
			//	�ڳ״� ���� �����غ��̴±���.
			//	
			//	isConversation1 = false;		//��ȣ�ۿ� ����.
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
		_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		break;
	case MORUSTATE::SPEAK:
		if (_speakCount == 0) {
			int arr[] = { 0, 1 };
			_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		break;
	case MORUSTATE::BROKEN:
		if (_speakCount == 0) {
			int arr[] = { 6, 3 };
			_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		break;
	case MORUSTATE::NOMONEY:
		if (_speakCount == 0) {
			int arr[] = { 0, 4 };
			_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr) / sizeof(int), 5, true);
		}
		else if (_speakCount == 100) {
			int arr[] = { 0 };
			_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr) / sizeof(int), 5, true);
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
		//������ �ҰųĴ� ������ ��ư �ΰ��� ��.
		//���� �� ���⸦ �������ٰ�?
		//�����Ѵ�(30 ���)
		//�����Ѵ�


		//�����Ѵ� ���ý�
		if (BUTTON->isClick("���-�����Ѵ�")) {
			BUTTON->buttonOff("���-�����Ѵ�");
			BUTTON->buttonOff("���-�����Ѵ�");
			isConversation1 = false;
			if (true)//������������ϸ�)
			{
				//����������.
				if (true)//��������) 
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
		}
	}
	if ((isConversation2 || isConversation3 || isConversation4) && (_speakCount > 100))
	{
		isConversation2 = false;
		isConversation3 = false;
		isConversation4 = false;
	}
}
