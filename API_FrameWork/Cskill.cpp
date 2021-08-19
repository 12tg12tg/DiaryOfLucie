#include "framework.h"
#include "Cskill.h"
#include "bulletManager.h"
Cskill::Cskill()
{
    IMAGE->addFrameImage("��ų�̹���", "images/skill/item_magic.bmp", 384, 96, 12, 3, true);
    IMAGE->addImage("�帰�̹���", WINSIZEX, WINSIZEY);
    BitBlt(IMAGE->findImage("�帰�̹���")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, getMemDC(), 0, 0, WHITENESS);
}

Cskill::~Cskill()
{
}

HRESULT Cskill::init()
{
    initForSkill();
    currentIndex = 0;
    skillnum = 0;
    skillUI[0] = RectMakeCenter(WINSIZEX/2-100, 569, 32, 32);
    skillUI[1] = RectMakeCenter(WINSIZEX / 2 - 34, 546, 32, 32);
    skillUI[2] = RectMakeCenter(WINSIZEX / 2 + 34, 546, 32, 32);
    skillUI[3] = RectMakeCenter(WINSIZEX / 2 + 100, 569, 32, 32);
    curRc = RectMakeCenter(WINSIZEX / 2 - 11, 611, 32, 32);

    nameRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 400, 30);
    infoRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, 500, 90);
    imgRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 32, 32);


    count = 0;
    isClick = false;
    return S_OK;
}

void Cskill::release()
{
}

void Cskill::update()
{
    skillFire();
    selectSKill();
}

void Cskill::render()
{
    uirender();
    showNewSkillInfo();
}

void Cskill::initForSkill()
{
    tagSkill newSkill;
    newSkill.name = "��Ű��Ÿ";
    newSkill.info = "���� �ټ���.\n���� ��ä�� ������ �ټ� ���� ���� �Ѹ���.";
    newSkill.burnMp = 1;
    newSkill.frameX = 7;
    newSkill.frameY = 0;
    newSkill.cooldown = 11;
    newSkill.key = 0;
    vList.push_back(newSkill);

    newSkill.name = "���̽����Ǿ�";
    newSkill.info = "�ܿ�ձ�.\n����â�� ���� ��� ������ ���� �������� �ִ� ������ �����.";
    newSkill.burnMp = 3;
    newSkill.frameX = 9;
    newSkill.frameY = 1;
    newSkill.cooldown = 18;
    newSkill.key = 1;
    vList.push_back(newSkill);

    newSkill.name = "���̽�Ʈ";
    newSkill.info = "������ ���� ����.\n��õ��� �̵��ӵ��� ���ݼӵ��� ������Ų��.";
    newSkill.burnMp = 1;
    newSkill.frameX = 10;
    newSkill.frameY = 0;
    newSkill.cooldown = 15;
    newSkill.duration = 8;
    newSkill.key = 2;
    vList.push_back(newSkill);

    /*...*/
}

void Cskill::addSkill()
{
    //�����ε��� �̱�
    int index = RND->getInt(vList.size());
    storage[skillnum] = vList[index];
    vList.erase(vList.begin() + index); 
    isSkillInfo = true;
    newSkill = storage[skillnum++];
}

void Cskill::skillFire()
{
    if (InputManager->isOnceKeyDown(VK_RBUTTON))
    {
        switch (storage[currentIndex].key)
        {
        case 0:
            _bm->getLucky_starInstance()->fire(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
                UTIL::getAngle(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, CAMMOUSEX, CAMMOUSEY), 0);
            break;
        case 1:
            _bm->getIce_spearInstance()->fire(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
                UTIL::getAngle(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, CAMMOUSEX, CAMMOUSEY), 0);
            break;
        case 2:
            _bm->getHasteInstance()->fire(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
                UTIL::getAngle(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, CAMMOUSEX, CAMMOUSEY), 0);
            break;
        default:
            break;
        }
    }
}

void Cskill::showNewSkillInfo()
{
    if (!isSkillInfo) return;
    //1.ȭ������
    //2.�����ķ���
    ZORDER->UIAlphaRender(IMAGE->findImage("�帰�̹���"), ZUIFADE, 100, 0, 0, 200);
    //3.Ŭ���� �����ǰų� count 500������ ����
    count++;
    if (count > 500 || (count>200 && INPUT->isOnceKeyDown(VK_LBUTTON))) {
        isSkillInfo = false;
    }
    ZORDER->UIFrameRender(IMAGE->findImage("��ų�̹���"), ZUIFADE, imgRc.bottom, imgRc.left, imgRc.top, newSkill.frameX, newSkill.frameY);
    ZORDER->UIDrawText(newSkill.name, ZUIFADE, nameRc,
        CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
            0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
        RGB(0, 0, 0), DT_LEFT | DT_VCENTER);
    ZORDER->UIDrawText(newSkill.info, ZUIFADE, infoRc,
        CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
            0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
        RGB(0, 0, 0), DT_LEFT | DT_VCENTER | DT_WORDBREAK);
}

void Cskill::selectSKill()
{
    if (InputManager->isOnceKeyDown('1')){
        currentIndex = 0;
    }
    else if (InputManager->isOnceKeyDown('2')) {
        currentIndex = 1;
    }
    else if (InputManager->isOnceKeyDown('3')) {
        currentIndex = 2;
    }
    else if (InputManager->isOnceKeyDown('4')) {
        currentIndex = 3;
    }
}

void Cskill::uirender()
{
	for (size_t i = 0; i < skillnum; i++)
	{
        if (_isDebug) {
            ZORDER->UIRectangle(skillUI[i], ZUISECOND);
            ZORDER->UIRectangle(curRc, ZUISECOND);
        }
		ZORDER->UIFrameRender(IMAGE->findImage("��ų�̹���"), ZUISECOND, 100, skillUI[i].left, skillUI[i].top,
			storage[i].frameX, storage[i].frameY);
	}
    if (skillnum != 0) {
        ZORDER->UIFrameRender(IMAGE->findImage("��ų�̹���"), ZUISECOND, 100, curRc.left, curRc.top,
            storage[currentIndex].frameX, storage[currentIndex].frameY);
    }
}
