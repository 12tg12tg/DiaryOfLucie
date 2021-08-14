#include "framework.h"
#include "moru.h"
#include "bulletManager.h"
moru::moru()
{
	IMAGE->addFrameImage("���", "images/object/moru.bmp", 288, 384, 2, 4, true);
	BUTTON->addButton("���-�����Ѵ�", 100, 100, 200, 40);
	BUTTON->buttonOn("���-�����Ѵ�");
	BUTTON->addButton("���-�����Ѵ�", 100, 100, 200, 40);
	BUTTON->buttonOn("���-�����Ѵ�");
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
	_interRc = RectMake(_footRc.left - RecWidth(PLAYER->getPlayerAddress().playerRect),
		_footRc.top - RecHeight(PLAYER->getPlayerAddress().playerRect),
		RecWidth(_footRc) + RecWidth(PLAYER->getPlayerAddress().playerRect)*2,
		RecHeight(_footRc) + RecHeight(PLAYER->getPlayerAddress().playerRect)*2);
	_state = MORUSTATE::NONE;
	int arr[] = { 0 };
	_ani = ANIMATION->addNoneKeyAnimation("���", arr, sizeof(arr)/sizeof(int), 5, true);
	_speakCount = 0;
	canInteraction = false;
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

void moru::checkRepair()
{
	//�浹�Ŵ������� inter���� �浹�� eŰ�� ������ canInteraction�� true�� ��.
	if (canInteraction)
	{
		//
		//������ �ҰųĴ� ������ ��ư �ΰ��� ��.
		



		//�����Ѵ� ���ý�
		//�� üũ �� 
			//���� ������ �� ���� �� Ȯ������. 

				//������ speekCount = 0 ���� �ٲٰ� ��ȭ����.
				
				//���н� BROKEN���·� �ٲٰ� ��ȭ����.
			

			//���� ������ NOMONEY ���·� �ٲٰ� ��ȭ����.



		//�����Ѵ� ���ý�
			//NONE ���·� ���ư���.





	}
}
