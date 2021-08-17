#include "framework.h"
#include "CplayerData.h"
#include "progressBar.h"

HRESULT CplayerData::init()
{
	this->imageInit();
	_Data =
	{
		1.5,
		0,
		_Data.walkspeed + _Data.equipspeed,

		 0,

		 10,
		 0,
		 _Data.defaultAtk + _Data.equipAtk,

		 10,
		 0,
		 _Data.defaultSkillPower + _Data.equipSkillPower,

		 0,

		 0
	};
	_isDebug = false;

	_level = 1;

	_lastMaxHP = 1;
	_defaultMaxHP = 5;
	_equipMaxHP = 0;
	_presentHP = _lastMaxHP + _defaultMaxHP + _equipMaxHP;
	_MaxHP = _lastMaxHP + _defaultMaxHP + _equipMaxHP;

	_defaultMaxMP = 3;
	_equipMaxMP = 0;
	_presentMP = _defaultMaxMP + _equipMaxMP;
	_MaxMP = _defaultMaxMP + _equipMaxMP;

	_defaultStamina = 100;
	_recoveryStaminaCoolTimeCount = 50;


	_EXP = 0;
	_getSkill = false;
	_gold = 0;

	UIalpha = 255;

	return S_OK;
}

void CplayerData::release()
{
	SAFE_DELETE(_EXPBar);
	SAFE_DELETE(_StaminaBar);
}

void CplayerData::update()
{
	_Data.presentSpeed = _Data.walkspeed + _Data.equipspeed;
	_Data.presentAtk = _Data.defaultAtk + _Data.equipAtk;
	_Data.presentSkillPower = _Data.defaultSkillPower + _Data.equipSkillPower;
	_MaxHP = _defaultMaxHP + _equipMaxHP + _lastMaxHP;
	_MaxMP = _defaultMaxMP + _equipMaxMP;

	this->recoveryStamina();
	_StaminaBar->setGauge(_defaultStamina, 100);
	_EXPBar->setGauge(_EXP, 100);
}

void CplayerData::render(HDC hdc)
{
<<<<<<< HEAD
	_StaminaBar->render();
	_EXPBar->render();
	//testrect.left,testrect.top
	ZORDER->UIRender(_layout_image, ZUIFIRST, 0, WINSIZEX / 2 - _layout_image->getWidth() / 2, 583);
	ZORDER->UIRender(_gold_G, ZUIFIRST, 0, WINSIZEX - 60, 20);
	goldRender(hdc);
	
	ZORDER->UIAlphaFrameRender(IMAGE->findImage("∑π∫ß"), ZUIFIRST, 0, 394, 639, _level, 0, UIalpha);
	//IMAGE->findImage("∑π∫ß")->alphaFrameRender(hdc, 394,639, _level,0, UIalpha);
	for (int i = 0; i < _MaxHP / 2 + _MaxHP % 2; i++)
	{
		if (_MaxHP % 2 == 1 && i == 0) {
			//IMAGE->findImage("¿€¿∫««≈Î")->alphaFrameRender(hdc, 436,614, 0, 0, UIalpha);
			ZORDER->UIAlphaFrameRender(IMAGE->findImage("¿€¿∫««≈Î"), ZUIFIRST, 0, 436, 614, 0, 0, UIalpha);
			continue;
		}
		ZORDER->UIAlphaFrameRender(IMAGE->findImage("««≈Î"), ZUIFIRST, 0, 429 - i * IMAGE->findImage("««≈Î")->getFrameWidth(), 606, 0, 0, UIalpha);
		//IMAGE->findImage("««≈Î")->alphaFrameRender(hdc, 429 - i * IMAGE->findImage("««≈Î")->getFrameWidth(), 606, 0, 0, UIalpha);
		if (i == _MaxHP / 2 + _MaxHP % 2 - 1)
			_heartstartX = 429 - i * IMAGE->findImage("««≈Î")->getFrameWidth();
	}
	for (int i = 0; i < _presentHP/2+_presentHP%2; i++)
	{
		if (_presentHP % 2 == 1 && i == _presentHP / 2 + _presentHP % 2-1) {
			ZORDER->UIAlphaFrameRender(IMAGE->findImage("¿€¿∫««≈Î"), ZUISECOND, 0, _heartstartX + i * IMAGE->findImage("««≈Î")->getFrameWidth() + 7, 614, 1, 0, UIalpha);
			//IMAGE->findImage("¿€¿∫««≈Î")->alphaFrameRender(hdc, _heartstartX + i * IMAGE->findImage("««≈Î")->getFrameWidth()+7, 614, 1, 0, UIalpha);
			continue;
		}
		ZORDER->UIAlphaFrameRender(IMAGE->findImage("««≈Î"), ZUISECOND, 0, _heartstartX + i * IMAGE->findImage("««≈Î")->getFrameWidth(), 606, 1, 0, UIalpha);
		//IMAGE->findImage("««≈Î")->alphaFrameRender(hdc, _heartstartX + i * IMAGE->findImage("««≈Î")->getFrameWidth(), 606, 1, 0, UIalpha);
	}

	for (int i = 0; i < _MaxMP; i++)
	{
		ZORDER->UIAlphaFrameRender(IMAGE->findImage("∏∂≥™≈Î"), ZUIFIRST, 0, 551 + i * IMAGE->findImage("∏∂≥™≈Î")->getFrameWidth(), 606, 0, 0, UIalpha);
		//IMAGE->findImage("∏∂≥™≈Î")->alphaFrameRender(hdc, 551 + i * IMAGE->findImage("∏∂≥™≈Î")->getFrameWidth(), 606, 0, 0, UIalpha);
	}
	for (int i = 0; i < _presentMP; i++)
	{
		ZORDER->UIAlphaFrameRender(IMAGE->findImage("∏∂≥™≈Î"), ZUISECOND, 0, 551 + i * IMAGE->findImage("∏∂≥™≈Î")->getFrameWidth(), 606, 1, 0, UIalpha);
		//IMAGE->findImage("∏∂≥™≈Î")->alphaFrameRender(hdc, 551 + i * IMAGE->findImage("∏∂≥™≈Î")->getFrameWidth(), 606 , 1, 0, UIalpha);
	}
=======
	this->renderUI(hdc);
>>>>>>> ÏÉàÎ°úÌÉúÏñ¥ÎÇòÏûêÎ∏åÎûúÏπò

	char str[256];
	//SetTextColor(hdc, RGB(0, 0, 255));
	if (_isDebug)
	{
<<<<<<< HEAD
		//sprintf_s(str, "√÷¥Î∏∂≥™≈Î? %d",_MaxMP );
		//TextOut(hdc, 0, WINSIZEY - 120, str, strlen(str));
		
		//ƒ´∏ﬁ∂Ûøµ«‚¿ª πﬁ¡ˆ æ ¥¬ ªÛ≈¬»Æ¿Œ.
=======
//		ƒ´∏ﬁ∂Ûøµ«‚¿ª πﬁ¡ˆ æ ¥¬ ªÛ≈¬»Æ¿Œ.
>>>>>>> ÏÉàÎ°úÌÉúÏñ¥ÎÇòÏûêÎ∏åÎûúÏπò
		wsprintf(str, "∏ ªÛ∏∂øÏΩ∫¿ßƒ°x,y? : %d, %d", (int)CAMMOUSEX, (int)CAMMOUSEY);
		ZORDER->UITextOut(str, ZUITHIRD, 0, WINSIZEY - 100, RGB(0, 0, 255));
		//TextOut(hdc, 0, WINSIZEY-100, str, lstrlen(str));
		sprintf_s(str, "«√∑π¿ÃæÓ x,y? %d , %d", (int)PLAYER->getPlayerAddress().x, (int)PLAYER->getPlayerAddress().y);
		ZORDER->UITextOut(str, ZUITHIRD, 0, WINSIZEY - 80, RGB(0, 0, 255));
		//TextOut(hdc, 0, WINSIZEY - 80, str, strlen(str));
		sprintf_s(str, "»≠∏ÈªÛ∏∂øÏΩ∫¿ßƒ°x,y? %d , %d", m_ptMouse.x, m_ptMouse.y);
		ZORDER->UITextOut(str, ZUITHIRD, 0, WINSIZEY - 60, RGB(0, 0, 255));
		//TextOut(hdc, 0, WINSIZEY - 60, str, strlen(str));
	}
}

void CplayerData::imageInit()
{
	_layout_image = IMAGE->addImage("«œ¥‹««≈Î∑π¿Ãæ∆øÙ", "images/UI/««≈ÎπË∞Ê.bmp", 230 * 1.3, 90 * 1.3, true);
	_gold_G = IMAGE->addImage("∞ÒµÂ¥‹¿ßG", "images/UI/∞ÒµÂG.bmp", 14*1.3, 19*1.3, true);
	IMAGE->addImage("«œ¥‹««≈Î∑π¿Ãæ∆øÙ", "images/UI/««≈ÎπË∞Ê.bmp", 230 * 1.3, 90 * 1.3, true);
	IMAGE->addFrameImage("∑π∫ß", "images/UI/∑π∫ßº˝¿⁄.bmp", 318 * 1.3, 19 * 1.3, 10, 1, true);
	IMAGE->addFrameImage("««≈Î", "images/UI/««≈Î.bmp", 48*1.3, 22*1.3, 2, 1, true);
	IMAGE->addFrameImage("¿€¿∫««≈Î", "images/UI/««≈Î.bmp", 48*1.3/2, 22*1.3/2, 2, 1, true);
	IMAGE->addFrameImage("∏∂≥™≈Î", "images/UI/∏∂≥™≈Î.bmp", 48 * 1.3, 24 * 1.3, 2, 1, true);
	IMAGE->addFrameImage("∞ÒµÂº˝¿⁄", "images/UI/∞ÒµÂº˝¿⁄.bmp", 140 * 1.3, 20 * 1.3, 10, 1, true);

	_EXPBar = new progressBar;
	_EXPBar->init("images/UI/∞‚ƒ°≈Î.bmp", "images/UI/∞‚ƒ°≈ÎπÈ.bmp",444,650,126*1.3,7 * 1.3);
	_StaminaBar = new progressBar;
	_StaminaBar->init("images/UI/Ω∫≈◊πÃ≥ «¡∑–∆Æ.bmp", "images/UI/Ω∫≈◊πÃ≥ πÈ.bmp", 398, 664, 166 * 1.3, 14 * 1.3);
}

void CplayerData::changeHP(int HP)
{
	_presentHP += HP;
	if (_presentHP < 0)
		_presentHP = 0;
	if (_presentHP > _MaxHP)
		_presentHP = _MaxHP;
}
int CplayerData::costHP(int cost,bool check)
{
	if (check) 
	{
		if (cost >= _presentHP)return false;
		else return true;
	}
	if (cost >= _presentHP)
	{
		int i = _presentHP-1;
		_presentHP = 1;
		return i;
	}
	else {
		_presentHP -= cost;
		return cost;
	}
}
void CplayerData::changeMP(int MP)
{
	_presentMP += MP;
	if (_presentMP < 0)
		_presentMP = 0;
	if (_presentMP > _MaxMP)
		_presentMP = _MaxMP;
}
int CplayerData::costMP(int cost,bool check)
{
	if (check)
	{
		if (cost > _presentMP) return false;
		else return true;
	}
	if (cost > _presentMP)
	{
		int i = _presentMP;
		_presentMP = 0;
		return i;
	}
	else {
		_presentMP -= cost;
		return cost;
	}
}

bool CplayerData::useStamina(int costStamina, bool check)
{
	if (check) 
	{
		if (_defaultStamina < costStamina)  return false;
		else return true;
	}
		_defaultStamina -= costStamina;
		_recoveryStaminaCoolTimeCount = 50;
		if (_defaultStamina < 0)
			_defaultStamina = 0;
}
void CplayerData::recoveryStamina()
{
	if (_recoveryStaminaCoolTimeCount) 
		_recoveryStaminaCoolTimeCount--;
	else if (_defaultStamina < 100)
	{
		if (PLAYER->getSTATEAddress() == STATE::IDLE)
			_defaultStamina += 1.5;
		else if (PLAYER->getSTATEAddress() == STATE::WALK)
			_defaultStamina += 1;
		else if (PLAYER->getSTATEAddress() == STATE::RUN)
			_defaultStamina+=0.5;
		if (_defaultStamina > 100) 
			_defaultStamina = 100;
	}
}
void CplayerData::recoveryStamina(int recovery)
{
	_defaultStamina += recovery;
	if (_defaultStamina > 100) 
		_defaultStamina = 100;
}

void CplayerData::goldRender(HDC hdc)
{
	if (_gold == 0)
	{
		ZORDER->UIFrameRender(IMAGE->findImage("∞ÒµÂº˝¿⁄"), ZUIFIRST, 0,  947, 20, 0, 0);
		//IMAGE->frameRender("∞ÒµÂº˝¿⁄", hdc, 947, 20, 0, 0);
		return;
	}
	int i = 1;
	for (int j=0; _gold/i>=1; j++)
	{
		ZORDER->UIFrameRender(IMAGE->findImage("∞ÒµÂº˝¿⁄"), ZUIFIRST, 0, 947 - j * IMAGE->findImage("∞ÒµÂº˝¿⁄")->getFrameWidth(), 20, (_gold / i) % 10, 0);
		//IMAGE->frameRender("∞ÒµÂº˝¿⁄", hdc, 947 - j * IMAGE->findImage("∞ÒµÂº˝¿⁄")->getFrameWidth() , 20,  (_gold/i)%10,0);
		i *= 10;																						
	}
}

void CplayerData::renderUI(HDC hdc)
{
	_StaminaBar->render();
	_EXPBar->render();
	_layout_image->render(hdc, WINSIZEX / 2 - _layout_image->getWidth() / 2, 583);
	_gold_G->render(hdc, WINSIZEX - 60, 20);
	goldRender(hdc);

	IMAGE->findImage("∑π∫ß")->alphaFrameRender(hdc, 394, 639, _level, 0, UIalpha);

	for (int i = 0; i < _MaxHP / 2 + _MaxHP % 2; i++)
	{
		if (_MaxHP % 2 == 1 && i == 0) {
			IMAGE->findImage("¿€¿∫««≈Î")->alphaFrameRender(hdc, 436, 614, 0, 0, UIalpha);
			continue;
		}
		IMAGE->findImage("««≈Î")->alphaFrameRender(hdc, 
			429 - (i%10)* IMAGE->findImage("««≈Î")->getFrameWidth(),
			606-(i/10)*IMAGE->findImage("««≈Î")->getFrameHeight(), 0, 0, UIalpha);
		if (i == _MaxHP / 2 + _MaxHP % 2 - 1) {
			_heartstartX = 429 - (i % 10) * IMAGE->findImage("««≈Î")->getFrameWidth();
			_heartstartY = 606 - (i / 10) * IMAGE->findImage("««≈Î")->getFrameHeight();
		}
	}
	for (int i = 0; i < _presentHP / 2 + _presentHP % 2; i++)
	{
		
		if (_presentHP % 2 == 1 && i == _presentHP / 2 + _presentHP % 2 - 1) {
			IMAGE->findImage("¿€¿∫««≈Î")->alphaFrameRender(hdc, _heartstartX + i * IMAGE->findImage("««≈Î")->getFrameWidth() + 7, _heartstartY+8, 1, 0, UIalpha);
			continue;
		}
		IMAGE->findImage("««≈Î")->alphaFrameRender(hdc, _heartstartX + i * IMAGE->findImage("««≈Î")->getFrameWidth(), _heartstartY, 1, 0, UIalpha);
		if ((_MaxHP / 2 + _MaxHP % 2 )%10==(i+1)%10) {
			_heartstartX -= 10 * IMAGE->findImage("««≈Î")->getFrameWidth();
			_heartstartY += IMAGE->findImage("««≈Î")->getFrameHeight();
		}
	}
	for (int i = 0; i < _MaxMP; i++)
	{
		IMAGE->findImage("∏∂≥™≈Î")->alphaFrameRender(hdc, 551 + (i % 10) * IMAGE->findImage("∏∂≥™≈Î")->getFrameWidth(),
			606- (i / 10) * IMAGE->findImage("∏∂≥™≈Î")->getFrameHeight(), 0, 0, UIalpha);
	}
	for (int i = 0; i < _presentMP; i++)
	{
		IMAGE->findImage("∏∂≥™≈Î")->alphaFrameRender(hdc, 551 + (i % 10) * IMAGE->findImage("∏∂≥™≈Î")->getFrameWidth(), 
			606 - (i/10) * IMAGE->findImage("∏∂≥™≈Î")->getFrameHeight(), 1, 0, UIalpha);
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

int CplayerData::getDamage()
{
	int damage=_Data.presentAtk;
	int critical = RND->getInt(100);
	if (critical < _Data.Critical) {
		damage *= 2;
	}
	else if (critical - _Data.Critical < (100 - _Data.Critical) / 2) {
		damage *= 0.1*RND->getFromInTo(1,10);
	}
	else {
		damage *= 1 + 0.1 * RND->getFromInTo(1, 10);
	}

	return damage;
}

void CplayerData::setEquip(int equipHP, int equipMaxHP, int equipMP, int equipMaxMP, float equipSpeed, int equipAtk, int equipAtkSpeed, int equipCritical, int equipSkillPower, int equipSkillCollTime)
{
	_presentHP += equipHP;
	_equipMaxHP += equipMaxHP;
	_presentMP += equipMP;
	_equipMaxMP += equipMaxMP;
	
	_Data.equipspeed += equipSpeed;
	_Data.equipAtk += equipAtk;
	_Data.AtkSpeed += equipAtkSpeed;
	_Data.Critical += equipCritical;
	_Data.equipSkillCoolTime += equipSkillPower;
	_Data.equipSkillCoolTime += equipSkillCollTime;
}

void CplayerData::takeOffEquip(int& equipHP, int equipMaxHP, int& equipMP, int equipMaxMP, float equipSpeed, int equipAtk, int equipAtkSpeed, int equipCritical, int equipSkillPower, int equipSkillCollTime)
{
	equipHP=costHP(equipMaxHP);
	_equipMaxHP -= equipMaxHP;
	equipMP = costMP(equipMaxMP);
	_equipMaxMP -= equipMaxMP;

	_Data.equipspeed -= equipSpeed;
	_Data.equipAtk -= equipAtk;
	_Data.AtkSpeed -= equipAtkSpeed;
	_Data.Critical -= equipCritical;
	_Data.equipSkillCoolTime -= equipSkillPower;
	_Data.equipSkillCoolTime -= equipSkillCollTime;
}