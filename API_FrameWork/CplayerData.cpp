#include "framework.h"
#include "CplayerData.h"


HRESULT CplayerData::init()
{
	_level = 1;
	_Critical = 5;

	_lastHP = 1;
	_defaultHp = 5;
	_defaultMaxHp = _defaultHp;
	_equipHP = 0;
	_MaxequipHP = 0;
	_presentHP = _lastHP+_defaultHp+_equipHP;
	_MaxHP = _lastHP + _defaultMaxHp + _MaxequipHP;

	_defaultMP=3;
	_equipMP = 0;
	_presentMP = _defaultMP + _equipMP;
	_MaxMP = _defaultMP + _MaxequipMP;

	_defaultAtk = 10;
	_defaultStamina = 100;

	return S_OK;
}

void CplayerData::release(){}

void CplayerData::update()
{
}

void CplayerData::render(HDC hdc)
{
	char str[256];
	SetTextColor(hdc, RGB(0, 0, 255));
	if(_isDebug){
	//RectangleMake(hdc, _player.playerRect); 
		sprintf_s(str, "현재 피통? % d",_presentHP);
		TextOut(hdc, 0, WINSIZEY - 100, str, strlen(str));
		sprintf_s(str, "최대피통? %d",_MaxHP );
		TextOut(hdc, 0, WINSIZEY - 120, str, strlen(str));}
}

void CplayerData::hitPlayer()
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
}