#include "framework.h"
#include "CplayerData.h"
#include "progressBar.h"

HRESULT CplayerData::init()
{
	this->imageInit();

	_isDebug = false;

	_level = 1;
	_Critical = 5;
	_defaultAtk = 10;

	_lastHP = 1;
	_lastMaxHP = _lastHP;
	_defaultHP = 5;
	_defaultMaxHP = _defaultHP;
	_equipHP = 0;
	_equipMaxHP = _equipHP;
	_presentHP = _lastHP+_defaultHP+_equipHP;
	_MaxHP = _lastHP + _defaultMaxHP + _equipMaxHP;

	_defaultMP=3;
	_defaultMaxMP = 3;
	_equipMP = 0;
	_equipMaxMP = _equipMP;
	_presentMP = _defaultMP + _equipMP;
	_MaxMP = _defaultMaxMP + _equipMaxMP;

	_defaultStamina = 100;
	_recoveryStaminaCoolTimeCount = 100;

	UIalpha = 255;

	_EXP = 0;
	_getSkill = false;
	_gold = 0;

	return S_OK;
}

void CplayerData::release()
{
	SAFE_DELETE(_EXPBar);
	SAFE_DELETE(_StaminaBar);
}

void CplayerData::update()
{
	_presentHP = _defaultHP + _equipHP + _lastHP;
	_MaxHP = _defaultMaxHP + _equipMaxHP + _lastMaxHP;
	_presentMP = _defaultMP + _equipMP;
	_MaxMP = _defaultMaxMP + _equipMaxMP;

	this->recoveryStamina();
	_StaminaBar->setGauge(_defaultStamina, 100);

	_EXPBar->setGauge(_EXP, 100);
}

void CplayerData::render(HDC hdc)
{
	_StaminaBar->render();
	_EXPBar->render();
	//testrect.left,testrect.top
	_layout_image->render(hdc,WINSIZEX/2-_layout_image->getWidth()/2,583);
	_gold_G->render(hdc,WINSIZEX-60,20);
	goldRender(hdc);
	
	IMAGE->findImage("����")->alphaFrameRender(hdc, 394,639, _level,0, UIalpha);
	
	for (int i = 0; i < _MaxHP / 2 + _MaxHP % 2; i++)
	{
		if (_MaxHP % 2 == 1 && i == 0) {
			IMAGE->findImage("��������")->alphaFrameRender(hdc, 436,614, 0, 0, UIalpha);
			continue;
		}
		IMAGE->findImage("����")->alphaFrameRender(hdc, 429 - i * IMAGE->findImage("����")->getFrameWidth(), 606, 0, 0, UIalpha);
		if (i == _MaxHP / 2 + _MaxHP % 2 - 1)
			_heartstartX = 429 - i * IMAGE->findImage("����")->getFrameWidth();
	}
	for (int i = 0; i < _presentHP/2+_presentHP%2; i++)
	{
		if (_presentHP % 2 == 1 && i == _presentHP / 2 + _presentHP % 2-1) {
			IMAGE->findImage("��������")->alphaFrameRender(hdc, _heartstartX + i * IMAGE->findImage("����")->getFrameWidth()+7, 614, 1, 0, UIalpha);
			continue;
		}
		IMAGE->findImage("����")->alphaFrameRender(hdc, _heartstartX + i * IMAGE->findImage("����")->getFrameWidth(), 606, 1, 0, UIalpha);
	}

	for (int i = 0; i < _MaxMP; i++)
	{
		IMAGE->findImage("������")->alphaFrameRender(hdc, 551 + i * IMAGE->findImage("������")->getFrameWidth(), 606, 0, 0, UIalpha);
	}
	for (int i = 0; i < _presentMP; i++)
	{
	IMAGE->findImage("������")->alphaFrameRender(hdc, 551 + i * IMAGE->findImage("������")->getFrameWidth(), 606 , 1, 0, UIalpha);
	}

	char str[256];
	SetTextColor(hdc, RGB(0, 0, 255));
	if(_isDebug)
	{
		/*
		sprintf_s(str, "�ִ븶����? %d",_MaxMP );
		TextOut(hdc, 0, WINSIZEY - 120, str, strlen(str));
		*/
	}
}

void CplayerData::imageInit()
{
	_layout_image = IMAGE->addImage("�ϴ����뷹�̾ƿ�", "images/UI/������.bmp", 230 * 1.3, 90 * 1.3, true);
	_gold_G = IMAGE->addImage("������G", "images/UI/���G.bmp", 14*1.3, 19*1.3, true);
	IMAGE->addImage("�ϴ����뷹�̾ƿ�", "images/UI/������.bmp", 230 * 1.3, 90 * 1.3, true);
	IMAGE->addFrameImage("����", "images/UI/��������.bmp", 318 * 1.3, 19 * 1.3, 10, 1, true);
	IMAGE->addFrameImage("����", "images/UI/����.bmp", 48*1.3, 22*1.3, 2, 1, true);
	IMAGE->addFrameImage("��������", "images/UI/����.bmp", 48*1.3/2, 22*1.3/2, 2, 1, true);
	IMAGE->addFrameImage("������", "images/UI/������.bmp", 48 * 1.3, 24 * 1.3, 2, 1, true);
	IMAGE->addFrameImage("������", "images/UI/������.bmp", 140 * 1.3, 20 * 1.3, 10, 1, true);

	_EXPBar = new progressBar;
	_EXPBar->init("images/UI/��ġ��.bmp", "images/UI/��ġ���.bmp",444,650,126*1.3,7 * 1.3);
	_StaminaBar = new progressBar;
	_StaminaBar->init("images/UI/���׹̳�����Ʈ.bmp", "images/UI/���׹̳ʹ�.bmp", 398, 664, 166 * 1.3, 14 * 1.3);
}

void CplayerData::hitPlayer(int damage)
{
	for (int i = 0; i < damage; i++) 
	{
		if (_defaultHP > 0) {
			_defaultHP--;
		}
		else if (_equipHP > 0) {
			_equipHP--;
		}
		else if (_lastHP > 0) {
			_lastHP--;
		}
		if (_presentHP == 0) {
			break;
		}
	}
}
void CplayerData::healPlayer(int recovery)
{

	for (int i = 0; i < recovery; i++)
	{
		if (_lastHP < _lastMaxHP) {
			_lastHP++;
		}
		else if (_equipHP < _equipMaxHP) {
			_equipHP++;
		}
		else if (_defaultHP < _defaultMaxHP) {
			_defaultHP++;
		}
		if (_presentHP == _MaxHP) {
			break;
		}
	}
}
bool CplayerData::useMana(int manaCost,bool Check)
{
	if (manaCost < _presentMP) { return false; }
	if (!Check) {
		for (int i = 0; i < manaCost; i++)
		{
			if (_defaultMP > 0) {
				_defaultMP--;
			}
			else if (_equipMP > 0) {
				_equipMP--;
			}
			if (_presentMP == 0) {
				break;
			}
		}
	}
	return true;
}
void CplayerData::recoveryMana(int recovery)
{
	for (int i = 0; i < recovery; i++)
	{
		if (_equipMP < _equipMaxMP) {
			_equipMP++;
		}
		else if (_defaultMP < _defaultMaxMP) {
			_defaultMP++;
		}
		if (_presentMP == _MaxMP) {
			break;
		}
	}
}

bool CplayerData::useStamina(int costStamina, bool check)
{
	if (_defaultStamina < costStamina&&check)  return false; 
	else if(check) return true;
		_defaultStamina -= costStamina;
		_recoveryStaminaCoolTimeCount = 100;
		if (_defaultStamina < 0)
			_defaultStamina = 0;
}
void CplayerData::recoveryStamina()
{
	if (_recoveryStaminaCoolTimeCount) 
		_recoveryStaminaCoolTimeCount--;
	else if (_defaultStamina < 100) {
		if (PLAYER->getSTATEAddress() == STATE::IDLE)
			_defaultStamina += 3;
		else if (PLAYER->getSTATEAddress() == STATE::WALK)
			_defaultStamina += 2;
		else if (PLAYER->getSTATEAddress() == STATE::RUN)
			_defaultStamina++;
		if (_defaultStamina >= 100) 
			_defaultStamina = 100;
	}
}
void CplayerData::recoveryStamina(int recovery)
{
	_defaultStamina += recovery;
	if (_defaultStamina >= 100) 
		_defaultStamina = 100;
}

//�����Լ�
//void CplayerData::goldRender(HDC hdc)
//{
//	if (_gold == 0) 
//	{
//		IMAGE->frameRender("������", hdc, 947, 20, 0, 0);
//		return;
//	}
//	int tempgold = _gold;
//	int i=1;
//	int j = 0;
//	
//	while (tempgold / i) 
//	{
//		j++;
//		i *= 10;
//		tempgold -= tempgold % i;
//	}
//	tempgold = _gold;
//	for (j; j > 0; j--)
//	{
//		i /= 10;																						
//		IMAGE->frameRender("������", hdc, 947 - (j - 1) * IMAGE->findImage("������")->getFrameWidth() , 20,  (int)tempgold/i,0);
//		tempgold -= tempgold / i * i;
//	}
//}

void CplayerData::goldRender(HDC hdc)
{
	if (_gold == 0)
	{
		IMAGE->frameRender("������", hdc, 947, 20, 0, 0);
		return;
	}
	int tempgold = _gold;
	int i = 1;
	for (int j=0; tempgold!=0; j++)
	{
		i *= 10;																						
		IMAGE->frameRender("������", hdc, 947 - j * IMAGE->findImage("������")->getFrameWidth() , 20,  (tempgold%i)/(i/10),0);
		tempgold -= tempgold % i;
	}
}

bool CplayerData::changeGold(int difference, bool check)
{
	if (_gold + difference < 0)  return false;
	else if(check) return true;
	_gold += difference;
}

void CplayerData::expUP(int exp)
{
	_EXP += exp;
	if (_EXP > 100) {
		if (_level < 9) 
		{
			_level++;
			_EXP -= 100;
			_getSkill == true;
		}
		else
		{
			_EXP = 100;
		}
	}
}