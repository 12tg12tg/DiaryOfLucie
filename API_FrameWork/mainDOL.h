#pragma once
#include "gameNode.h"
#include "bulletManager.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "mapManager.h"
#include "DOL_Title.h"
#include "loading.h"
#include "Cskill.h"
class mainDOL : public gameNode
{
//DOL ���� �Ŵ��� �ν��Ͻ�
private:
	bulletManager*		_bm;
	collisionManager*	_cm;
	monsterManager*		_mm;
	mapManager*			_mapm;
	Cskill*				_sk;
//-----------------------------
//������ �귻ġ �ν��Ͻ�
private:
	DOL_Title* _DOLtitle;
	loading* _loading;
	bool canUpdate;
	bool soundplay;
//���� ���� ����
private:
	enum class DOLSTATE
	{
		LOADING,
		INMAP,
		GETSKILL,
	};
	DOLSTATE _state;
//-----------------------------
//����׸�� ����
private:
	bool _isDebug;
//-----------------------------
public:
	mainDOL();
	~mainDOL();

	HRESULT init();
	void release();
	void update();
	void render();

	void gameInit();
	void initForsound();
	void setIsdebug(bool isDebug) {
		_isDebug = isDebug;
		switch (_state)
		{
		case mainDOL::DOLSTATE::LOADING:
			BUTTON->setIsDebug(_isDebug);
			break;
		case mainDOL::DOLSTATE::INMAP:
			_bm->setIsDebug(_isDebug);
			_cm->setIsDebug(_isDebug);
			_mm->setIsDebug(_isDebug);
			_mapm->setIsDebug(_isDebug);
			_sk->setIsDebug(_isDebug);
			BUTTON->setIsDebug(_isDebug);
			PLAYER->setIsDebug(_isDebug);
			PLAYERDATA->setIsDebug(_isDebug);
			ITEM->setIsDebug(_isDebug);
			INVENTORY->setIsDebug(_isDebug);
			break;
		case mainDOL::DOLSTATE::GETSKILL:
			_sk->setIsDebug(_isDebug);
			break;
		default:
			break;
		}
	}
};

