#include "framework.h"
#include "Cskill.h"
#include "bulletManager.h"
Cskill::Cskill()
{
    IMAGE->addFrameImage("��ų�̹���", "images/skill/item_magic.bmp", 384, 96, 12, 3, true);
    IMAGE->addImage("����ų", "images/skill/newskill.bmp", 160, 32, true);
    IMAGE->addImage("��Ÿ�ӵ���", "images/skill/coolover.bmp", 40, 40, true);
    IMAGE->addImage("��Ÿ�ӵ���Ȯ��", "images/skill/coolover.bmp", 40*1.4, 40*1.4, true);
    IMAGE->addImage("���Ұ��ɵ���", "images/skill/cooloverunable.bmp", 40, 40, true);
    IMAGE->addImage("���Ұ��ɵ���Ȯ��", "images/skill/cooloverunable.bmp", 40*1.4, 40*1.4, true);
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
    curRc = RectMakeCenter(WINSIZEX / 2 - 7, 611, 32, 32);

    nameRc = RectMake(WINSIZEX / 2-150-80, WINSIZEY / 2, 400, 30);
    infoRc = RectMake(WINSIZEX / 2-150-80, WINSIZEY / 2 + 50, 600, 90);
    imgRc = RectMakeCenter(WINSIZEX / 2+50, WINSIZEY / 2 - 50, 64, 64);


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
    coolDown();
    checkDuration();
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
    newSkill.cooldown = 0;
    newSkill.cooltime = 11;
    newSkill.duration = 8;
    newSkill.key = 0;
    newSkill.isCool = false;
    newSkill.count = 0;
    newSkill.durationDown = 0;
    newSkill.isOn = false;
    vList.push_back(newSkill);

    newSkill.name = "���̽����Ǿ�";
    newSkill.info = "�ܿ�ձ�.\n����â�� ���� ��� ������ ���� �������� �ִ� ������ �����.";
    newSkill.burnMp = 3;
    newSkill.frameX = 9;
    newSkill.frameY = 1;
    newSkill.cooldown = 0;
    newSkill.cooltime = 18;
    newSkill.key = 1;
    newSkill.isCool = false;
    newSkill.count = 0;
    newSkill.duration = 0;
    newSkill.durationDown = 0;
    newSkill.isOn = false;
    vList.push_back(newSkill);

    newSkill.name = "���̽�Ʈ";
    newSkill.info = "������ ���� ����.\n��õ��� �̵��ӵ��� ���ݼӵ��� ������Ų��.";
    newSkill.burnMp = 1;
    newSkill.frameX = 10;
    newSkill.frameY = 0;
    newSkill.cooldown = 0;
    newSkill.cooltime = 15;
    newSkill.duration = 8;
    newSkill.key = 2;
    newSkill.isCool = false;
    newSkill.count = 0;
    newSkill.durationDown = 0;
    newSkill.isOn = false;
    vList.push_back(newSkill);

    /*...*/
}

void Cskill::addSkill()
{
    //�����ε��� �̱�
    if (vList.size() == 0) return;
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
        if (skillnum==0 || storage[currentIndex].isCool) return;
        if (PLAYERDATA->costMP(storage[currentIndex].burnMp, true)) {
            PLAYERDATA->costMP(storage[currentIndex].burnMp);
            storage[currentIndex].isCool = true;
            storage[currentIndex].isOn = true;
        }
    }
}


void Cskill::showNewSkillInfo()
{
    if (!isSkillInfo) return;
    //1.ȭ������
    //2.�����ķ���
    ZORDER->UIAlphaRender(IMAGE->findImage("�帰�̹���"), ZUIFADE, 100, 0, 0, 185);
    ZORDER->UIRender(IMAGE->findImage("����ų"), ZUIFADE, 101, 90 + WINSIZEX / 2 - IMAGE->findImage("����ų")->getWidth(),
        imgRc.top - 100);
    //3.Ŭ���� �����ǰų� count 500������ ����
    count++;
    if (count > 500 || (count>200 && INPUT->isOnceKeyDown(VK_LBUTTON))) {
        isSkillInfo = false;
        count = 0;
    }
    ZORDER->UIStretchFrameRender(IMAGE->findImage("��ų�̹���"), ZUIFADE, imgRc.bottom, imgRc.left, imgRc.top, newSkill.frameX, newSkill.frameY, 2);
   
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
    if (skillnum > 0 && InputManager->isOnceKeyDown('1')){
        currentIndex = 0;
    }
    else if (skillnum > 1 && InputManager->isOnceKeyDown('2')) {
        currentIndex = 1;
    }
    else if (skillnum > 2 && InputManager->isOnceKeyDown('3')) {
        currentIndex = 2;
    }
    else if (skillnum > 3 && InputManager->isOnceKeyDown('4')) {
        currentIndex = 3;
    }
}

void Cskill::uirender()
{
    BYTE addAlpha = PLAYERDATA->getUIAlpha();
    //4���� ��ųǥ��
	for (size_t i = 0; i < skillnum; i++)
	{
        if (_isDebug) {
            ZORDER->UIRectangle(skillUI[i], ZUISECOND);
            ZORDER->UIRectangle(curRc, ZUISECOND);
        }
		ZORDER->UIAlphaFrameRender(IMAGE->findImage("��ų�̹���"), ZUISECOND, 99, skillUI[i].left, skillUI[i].top,
			storage[i].frameX, storage[i].frameY, addAlpha);
        if (storage[i].isCool)
        {
            int ctime = (int)(storage[i].cooltime - storage[i].cooldown);
            float ratio = (float)ctime / storage[i].cooltime;
            //�ش�ڽ��� �帴�� �̹��� ���ķ����ϰ�
            BYTE thisalpha = (addAlpha > 180) ? 180 : addAlpha;
            ZORDER->UIAlphaRender(IMAGE->findImage("���Ұ��ɵ���"), ZUISECOND, 100, skillUI[i].left - 4, skillUI[i].top - 4, thisalpha);
            thisalpha = (addAlpha > 255 * ratio) ? 255 * ratio : addAlpha;
            ZORDER->UIAlphaRender(IMAGE->findImage("��Ÿ�ӵ���"),
                ZUISECOND, 101,
                skillUI[i].left - 4, skillUI[i].top - 4 + IMAGE->findImage("��Ÿ�ӵ���")->getHeight() - IMAGE->findImage("��Ÿ�ӵ���")->getHeight() * ratio,
                0, IMAGE->findImage("��Ÿ�ӵ���")->getHeight() - IMAGE->findImage("��Ÿ�ӵ���")->getHeight()*ratio,
                IMAGE->findImage("��Ÿ�ӵ���")->getWidth(),
                IMAGE->findImage("��Ÿ�ӵ���")->getHeight()*ratio,
                thisalpha);
            //�ܿ� ��Ÿ�� ǥ��
            ZORDER->UIDrawText(to_string(ctime), ZUISECOND,
                { skillUI[i].left-4, skillUI[i].top+4, skillUI[i].right+4, skillUI[i].bottom+4},
                CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
                    0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
                RGB(255, 255*(1-ratio), 255 * (1 - ratio)), DT_CENTER | DT_VCENTER);
        }
	}
    //���� �������� ��ų ǥ��.
    if (skillnum != 0) {
        ZORDER->UIAlphaFrameRender(IMAGE->findImage("��ų�̹���"), ZUISECOND, -2, curRc.left, curRc.top-2,
            storage[currentIndex].frameX, storage[currentIndex].frameY, addAlpha);
        //���� ǥ��
        ZORDER->UIDrawText(to_string(storage[currentIndex].burnMp), ZUISECOND,
            { curRc.left - 4, 623+3, curRc.right + 4, 642+3 },
            CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
                0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
            RGB(255, 255, 255), DT_CENTER | DT_VCENTER);
        if (storage[currentIndex].isCool)
        {
            int ctime = (int)(storage[currentIndex].cooltime - storage[currentIndex].cooldown);
            float ratio = (float)ctime / storage[currentIndex].cooltime;
            //�ش�ڽ��� �帴�� �̹��� ���ķ����ϰ�
            BYTE thisalpha = (addAlpha > 180) ? 180 : addAlpha;
            ZORDER->UIAlphaRender(IMAGE->findImage("���Ұ��ɵ���Ȯ��"), ZUISECOND, -1, curRc.left - 4 - 8, curRc.top - 4 - 6, thisalpha);
            thisalpha = (addAlpha > 255 * ratio) ? 255 * ratio : addAlpha;
            ZORDER->UIAlphaRender(IMAGE->findImage("��Ÿ�ӵ���Ȯ��"),
                ZUISECOND, 0,
                curRc.left - 4 - 8, curRc.top - 4 - 8 + IMAGE->findImage("��Ÿ�ӵ���Ȯ��")->getHeight() - IMAGE->findImage("��Ÿ�ӵ���Ȯ��")->getHeight() * ratio,
                0, IMAGE->findImage("��Ÿ�ӵ���Ȯ��")->getHeight() - IMAGE->findImage("��Ÿ�ӵ���Ȯ��")->getHeight() * ratio,
                IMAGE->findImage("��Ÿ�ӵ���Ȯ��")->getWidth(),
                IMAGE->findImage("��Ÿ�ӵ���Ȯ��")->getHeight() * ratio,
                thisalpha);
            //�ܿ� ��Ÿ�� ǥ��
            ZORDER->UIDrawText(to_string(ctime), ZUISECOND,
                { curRc.left - 4, curRc.top + 4, curRc.right + 4, curRc.bottom + 4 },
                CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
                    0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("HY�߰��")),
                RGB(255, 255 * (1 - ratio), 255 * (1 - ratio)), DT_CENTER | DT_VCENTER);
        }
    }
}

void Cskill::coolDown()
{
    for (size_t i = 0; i < skillnum; i++)
    {
        if (storage[i].isCool)
        {
            storage[i].cooldown += TIME->getElapsedTime();
            if (storage[i].cooldown >= storage[i].cooltime)
            {
                storage[i].isCool = false;
                storage[i].cooldown = 0;
            }
        }
    }
}

void Cskill::checkDuration()
{
    for (size_t i = 0; i < skillnum; i++)
    {
        if (!storage[i].isOn) continue;

        switch (storage[i].key)
        {
        case 0:
            if (storage[i].count % 3 == 0 && storage[i].count < 10)
                _bm->getLucky_starInstance()->fire(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
                    UTIL::getAngle(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, CAMMOUSEX, CAMMOUSEY), 0);
            /*���ӽð����� Ʈ���ü� ���� �ο��ϴ� ����*/
            break;
        case 1:
            _bm->getIce_spearInstance()->fire(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
                UTIL::getAngle(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, CAMMOUSEX, CAMMOUSEY), 0);
            break;
        case 2:
            if (storage[i].count == 0)
                _bm->getHasteInstance()->fire(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y,
                    UTIL::getAngle(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, CAMMOUSEX, CAMMOUSEY), 0);
            /*���ӽð����� �̼� ���� ����*/
            break;
        default:
            break;
        }

        storage[i].count++;
        storage[i].durationDown += TIME->getElapsedTime();
        if (storage[i].durationDown >= storage[i].duration)
        {
            storage[i].isOn = false;
            storage[i].durationDown = 0;
            storage[i].count = 0;
        }
    }
}
