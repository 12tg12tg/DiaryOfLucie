#include "framework.h"
#include "CplayerData.h"
#include "progressBar.h"

HRESULT CplayerData::init()
{
	testrect = RectMakeCenter(30, 30, 30, 30);
	this->imageInit();

	_isDebug = false;

	_level = 1;
	_Critical = 5;

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
	_defaultAtk = 10;
	_defaultStamina = 100;

	UIalpha = 255;

	return S_OK;
}

void CplayerData::release()
{
	SAFE_DELETE(_EXP);
}

void CplayerData::update()
{
	_presentHP = _defaultHP + _equipHP + _lastHP;
	_MaxHP = _defaultMaxHP + _equipMaxHP + _lastMaxHP;
	_presentMP = _defaultMP + _equipMP;
	_MaxMP = _defaultMaxMP + _equipMaxMP;

	dragUI();
	_EXP->setGauge(40, 100);
}

void CplayerData::render(HDC hdc)
{
	_EXP->render();
	//testrect.left,testrect.top
	
	_layout_image->render(hdc,WINSIZEX/2-_layout_image->getWidth()/2,583);
	
	IMAGE->findImage("레벨")->alphaFrameRender(hdc, 394,639, _level,0, UIalpha);
	
	for (int i = 0; i < _MaxHP / 2 + _MaxHP % 2; i++)
	{
		if (_MaxHP % 2 == 1 && i == 0) {
			IMAGE->findImage("작은피통")->alphaFrameRender(hdc, 436,614, 0, 0, UIalpha);
			continue;
		}
		IMAGE->findImage("피통")->alphaFrameRender(hdc, 429 - i * IMAGE->findImage("피통")->getFrameWidth(), 606, 0, 0, UIalpha);
		if (i == _MaxHP / 2 + _MaxHP % 2 - 1)
			_heartstartX = 429 - i * IMAGE->findImage("피통")->getFrameWidth();
	}
	for (int i = 0; i < _presentHP/2+_presentHP%2; i++)
	{
		if (_presentHP % 2 == 1 && i == _presentHP / 2 + _presentHP % 2-1) {
			IMAGE->findImage("작은피통")->alphaFrameRender(hdc, _heartstartX + i * IMAGE->findImage("피통")->getFrameWidth()+7, 614, 1, 0, UIalpha);
			continue;
		}
		IMAGE->findImage("피통")->alphaFrameRender(hdc, _heartstartX + i * IMAGE->findImage("피통")->getFrameWidth(), 606, 1, 0, UIalpha);
	}

	for (int i = 0; i < _MaxMP; i++)
	{
		IMAGE->findImage("마나통")->alphaFrameRender(hdc, 551 + i * IMAGE->findImage("마나통")->getFrameWidth(), 606, 0, 0, UIalpha);
	}
	for (int i = 0; i < _presentMP; i++)
	{
	IMAGE->findImage("마나통")->alphaFrameRender(hdc, 551 + i * IMAGE->findImage("마나통")->getFrameWidth(), 606 , 1, 0, UIalpha);
	}

	char str[256];
	SetTextColor(hdc, RGB(0, 0, 255));
	if(_isDebug)
	{
		RectangleMake(hdc, testrect); 
		sprintf_s(str, "현재마나통? %d",_presentMP);
		TextOut(hdc, 0, WINSIZEY - 100, str, strlen(str));
		sprintf_s(str, "최대마나통? %d",_MaxMP );
		TextOut(hdc, 0, WINSIZEY - 120, str, strlen(str));
		sprintf_s(str, "현재 UI 좌상단? %d, %d", testrect.left, testrect.top);
		TextOut(hdc, testrect.left,testrect.top+30, str, strlen(str));
	}
}

void CplayerData::imageInit()
{
	_layout_image = IMAGE->addImage("하단피통레이아웃", "images/UI/피통배경.bmp", 230 * 1.3, 90 * 1.3, true);
	_level_image = IMAGE->addFrameImage("레벨", "images/UI/레벨숫자.bmp", 320 * 1.3, 19 * 1.3, 10, 1, true);
	IMAGE->addFrameImage("피통", "images/UI/피통.bmp", 48*1.3, 22*1.3, 2, 1, true);
	IMAGE->addFrameImage("작은피통", "images/UI/피통.bmp", 48*1.3/2, 22*1.3/2, 2, 1, true);
	IMAGE->addFrameImage("마나통", "images/UI/마나통.bmp", 48 * 1.3, 24 * 1.3, 2, 1, true);

	_EXP = new progressBar;
	_EXP->init("images/UI/스테미너프론트.bmp", "images/UI/스테미너프론트.bmp",398,664,166*1.3,14 * 1.3);
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

void CplayerData::dragUI()
{
	if (INPUT->isOnceKeyDown(VK_RBUTTON) && m_ptMouse.x > testrect.left && m_ptMouse.x < testrect.right &&
		m_ptMouse.y>testrect.top && m_ptMouse.y < testrect.bottom)
	{
		tempX = m_ptMouse.x - testrect.left;
		tempY = m_ptMouse.y - testrect.top;
	}
	else if (INPUT->isStayKeyDown(VK_RBUTTON) && m_ptMouse.x > testrect.left && m_ptMouse.x < testrect.right &&
		m_ptMouse.y>testrect.top && m_ptMouse.y < testrect.bottom)
	{
		width = testrect.right - testrect.left;
		height = testrect.bottom - testrect.top;
		testrect = RectMake(m_ptMouse.x - tempX, m_ptMouse.y - tempY, width, height);
	}
}