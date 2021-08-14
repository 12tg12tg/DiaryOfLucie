#include "framework.h"
#include "CplayerData.h"

HRESULT CplayerData::init()
{
	this->imageInit();

	testrect = RectMakeCenter(30, 30, 30, 30);
	_isDebug = false;

	_level = 1;
	_Critical = 5;

	_lastHP = 1;
	_lastMaxHP = _lastHP;
	_defaultHp = 5;
	_defaultMaxHp = _defaultHp;
	_equipHP = 0;
	_equipMaxHP = _equipHP;
	_presentHP = _lastHP+_defaultHp+_equipHP;
	_MaxHP = _lastHP + _defaultMaxHp + _equipMaxHP;

	_defaultMP=2;
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

void CplayerData::release(){}

void CplayerData::update()
{
	_presentHP = _defaultHp + _equipHP + _lastHP;
	_MaxHP = _defaultMaxHp + _equipMaxHP + _lastMaxHP;
	_presentMP = _defaultMP + _equipMP;
	_MaxMP = _defaultMaxMP + _equipMaxMP;

	dragUI();
}

void CplayerData::render(HDC hdc)
{
	//testrect.left,testrect.top
	
	_layout_image->render(hdc,WINSIZEX/2-_layout_image->getWidth()/2,583);
	
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
		RectangleMake(hdc, testrect); 
		sprintf_s(str, "���縶����? %d",_presentMP);
		TextOut(hdc, 0, WINSIZEY - 100, str, strlen(str));
		sprintf_s(str, "�ִ븶����? %d",_MaxMP );
		TextOut(hdc, 0, WINSIZEY - 120, str, strlen(str));
		sprintf_s(str, "���� UI �»��? %d, %d", testrect.left, testrect.top);
		TextOut(hdc, testrect.left,testrect.top+30, str, strlen(str));
	}
}

void CplayerData::imageInit()
{
	_layout_image = IMAGE->addImage("�ϴ����뷹�̾ƿ�", "images/UI/������.bmp", 230 * 1.3, 90 * 1.3, true);
	_level_image = IMAGE->addFrameImage("����", "images/UI/��������.bmp", 320 * 1.3, 19 * 1.3, 10, 1, true);
	IMAGE->addFrameImage("����", "images/UI/����.bmp", 48*1.3, 22*1.3, 2, 1, true);
	IMAGE->addFrameImage("��������", "images/UI/����.bmp", 48*1.3/2, 22*1.3/2, 2, 1, true);
	IMAGE->addFrameImage("������", "images/UI/������.bmp", 48 * 1.3, 24 * 1.3, 2, 1, true);

}

void CplayerData::hitPlayer(int damage)
{
	for (int i = 0; i < damage; i++) 
	{
		if (_defaultHp > 0) {
			_defaultHp--;
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
		else if (_defaultHp < _defaultMaxHp) {
			_defaultHp++;
		}
		if (_presentHP == _MaxHP) {
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