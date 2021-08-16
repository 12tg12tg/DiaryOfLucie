#include "framework.h"
#include "Cmap.h"

Cmap::Cmap()
{
	IMAGE->addImage("95���", "images/map/ground95.bmp", 1104,960, true, RGB(255, 0, 255));
	_collisionMap =IMAGE->addImage("95�ȼ�", "images/map/!m95.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("95����", "images/map/Par95.bmp", 1104, 960, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0,454, 25, 150);//left
	_door[1].Door = RectMake(482, 0, 140, 25); //top
	_door[2].Door = RectMake(1085, 450, 25 , 150);//right
	_door[3].Door = RectMake(476, 940,140, 25); //bottom
	monpos[0] = { 380,380 };
	monpos[1] = { 670,640 };
	monpos[2] = { 432,522 };
	monpos[3] = { 720,500 };
}

Cmap::~Cmap()
{
}

HRESULT Cmap::init()
{
	
	//summonMon(4);
	
	return S_OK;
}

void Cmap::release()
{
}

void Cmap::update()
{
}

void Cmap::render()
{
	

	ZORDER->ZorderRender(IMAGE->findImage("95���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("95����"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("95�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
	
}

Cmap2::Cmap2()
{
	IMAGE->addImage("57���", "images/map/ground57.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("57�ȼ�","images/map/!m57.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("57����", "images/map/Par57.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 404 , 25, 70);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 358,25 , 120);//right
	_door[3].Door = RectMake(428, 655,150, 25); //bottom
	monpos[0] = { 445,570 };
	monpos[1] = { 624,263 };
	monpos[2] = { 464,282 };
	monpos[3] = { 525,342 };
}

Cmap2::~Cmap2()
{
}

HRESULT Cmap2::init()
{
	
	//summonMon(4);

	return S_OK;
}

void Cmap2::release()
{
}

void Cmap2::update()
{
}

void Cmap2::render()
{

	ZORDER->ZorderRender(IMAGE->findImage("57���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("57����"), ZABOVEMAP, WINSIZEX, 0, 0);

	if(_isDebug) ZORDER->ZorderRender(IMAGE->findImage("57�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door,ZEFFECT1);
}

Cmap3::Cmap3()
{
	IMAGE->addImage("104���", "images/map/ground104.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("104�ȼ�", "images/map/!m104.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("104����", "images/map/Par104.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0,333, 20,100);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 321, 25,110 );//right
	_door[3].Door = RectMake(434, 754, 140, 25); //bottom
	monpos[0] = { 350,350 };
	monpos[1] = { 495,446 };
	monpos[2] = { 477,544 };
	monpos[3] = { 760,437 };
}

Cmap3::~Cmap3()
{
}

HRESULT Cmap3::init()
{
	

	//summonMon(4);
	return S_OK;
}

void Cmap3::release()
{

}

void Cmap3::update()
{
}

void Cmap3::render()
{
	
	
	ZORDER->ZorderRender(IMAGE->findImage("104���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("104����"), ZABOVEMAP, WINSIZEX, 0, 0);
	if(_isDebug) ZORDER->ZorderRender(IMAGE->findImage("104�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}
	

Cmap4::Cmap4()
{
	IMAGE->addImage("105���", "images/map/ground105.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("105�ȼ�", "images/map/!m105.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("105����", "images/map/Par105.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 268, 25,160);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 333 , 25, 100);//right
	_door[3].Door = RectMake(433, 750, 145, 25); //bottom
	monpos[0] = { 414,366 };
	monpos[1] = { 542,421 };
	monpos[2] = { 764,410 };
	monpos[3] = { 537,646 };
}

Cmap4::~Cmap4()
{
}

HRESULT Cmap4::init()
{
	
	//summonMon(4);

	return S_OK;
}

void Cmap4::release()
{
}

void Cmap4::update()
{
}

void Cmap4::render()
{

	ZORDER->ZorderRender(IMAGE->findImage("105���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("105����"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("105�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door,ZEFFECT1);
}

Cmap5::Cmap5()
{
	IMAGE->addImage("115���", "images/map/ground115.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("115�ȼ�", "images/map/!m115.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("115����", "images/map/Par115.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 353, 25,150);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 356, 25, 140);//right
	_door[3].Door = RectMake(428,650 , 150, 25); //bottom
	monpos[0] = { 429,347 };
	monpos[1] = {566,353 };
	monpos[2] = {497,230 };
	monpos[3] = { 756,423 };
}

Cmap5::~Cmap5()
{
}

HRESULT Cmap5::init()
{
	//summonMon(4);
	return S_OK;
}

void Cmap5::release()
{
	
}

void Cmap5::update()
{
}

void Cmap5::render()
{


	ZORDER->ZorderRender(IMAGE->findImage("115���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("115����"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("115�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap6::Cmap6()
{
	IMAGE->addImage("50���", "images/map/ground50.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("50�ȼ�", "images/map/!m50.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("50����", "images/map/Par50.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 312, 25, 130);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 303, 25, 130);//right
	_door[3].Door = RectMake(430, 750, 150, 25); //bottom
	monpos[0] = { 632,406 };
	monpos[1] = {459,462 };
	monpos[2] = {367,276 };
	monpos[3] = { 692,392};
}

Cmap6::~Cmap6()
{
}

HRESULT Cmap6::init()
{
	//summonMon(4);

	return S_OK;
}

void Cmap6::release()
{
}

void Cmap6::update()
{
}

void Cmap6::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("50���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("50����"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("50�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap7::Cmap7()
{
	IMAGE->addImage("51���", "images/map/ground51.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("51�ȼ�", "images/map/!m51.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("51����", "images/map/Par51.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 404, 25, 70);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 358, 25, 120);//right
	_door[3].Door = RectMake(428, 655, 150, 25); //bottom
	monpos[0] = { 470,263 };
	monpos[1] = { 473,573 };
	monpos[2] = { 681,381 };
	monpos[3] = { 330,440 };
}

Cmap7::~Cmap7()
{
}

HRESULT Cmap7::init()
{
	//summonMon(4);

	return S_OK;
}

void Cmap7::release()
{
}

void Cmap7::update()
{
}

void Cmap7::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("51���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("51����"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("51�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap8::Cmap8()
{
	IMAGE->addImage("100���", "images/map/ground100.bmp", 1008,768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("100�ȼ�", "images/map/!m100.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("100����", "images/map/Par100.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 312, 25, 130);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 303, 25, 130);//right
	_door[3].Door = RectMake(430, 750, 150, 25); //bottom
	monpos[0] = { 662,402 };
	monpos[1] = { 606,480 };
	monpos[2] = {351,272 };
	monpos[3] = { 593,260 };
}

Cmap8::~Cmap8()
{
}

HRESULT Cmap8::init()
{
	//summonMon(4);

	return S_OK;
}

void Cmap8::release()
{
}

void Cmap8::update()
{
}

void Cmap8::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("100���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("100����"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("100�ȼ�"), ZCOLMAP, WINSIZEY, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap9::Cmap9()
{
	IMAGE->addImage("108���", "images/map/ground108.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("108�ȼ�", "images/map/!m108.bmp", 1008, 672 , true, RGB(255, 0, 255));
	IMAGE->addImage("108����", "images/map/Par108.bmp", 1008, 672 , true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433,0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650,160,25); //bottom
	monpos[0] = { 504,156 };
	monpos[1] = { 624,263 };
	monpos[2] = { 464,282 };
	monpos[3] = { 525,342 };
}

Cmap9::~Cmap9()
{
}

HRESULT Cmap9::init()
{
	//summonMon(4);

	return S_OK;
}

void Cmap9::release()
{
}

void Cmap9::update()
{
}

void Cmap9::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("108���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("108����"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("108�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap10::Cmap10()
{
	IMAGE->addImage("114���", "images/map/ground114.bmp", 1108,672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("114�ȼ�", "images/map/!m114.bmp", 1108, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("114����", "images/map/Par114.bmp", 1108, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMakeCenter(0, 426, 50, 100);//left
	_door[1].Door = RectMake(474, 0, 170, 25); //top
	_door[2].Door = RectMake(1005, 424, 25, 100);//right
	_door[3].Door = RectMake(465, 655, 180, 25); //bottom
}

Cmap10::~Cmap10()
{
}

HRESULT Cmap10::init()
{
	

	return S_OK;
}

void Cmap10::release()
{
}

void Cmap10::update()
{
}

void Cmap10::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("114���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("114����"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("114�ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

chestMap::chestMap()
{
	IMAGE->addImage("���ڹ���", "images/map/chestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("���ڹ��ȼ�", "images/map/!mchestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("���ڹ氡��", "images/map/ParchestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom
	_chest = new chest;
	_chest->add(504, 336);
}

chestMap::~chestMap()
{
}

HRESULT chestMap::init()
{
	
	return S_OK;
}

void chestMap::release()
{
	SAFE_DELETE(_chest);
}

void chestMap::update()
{
	_chest->update(bm);
}

void chestMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("���ڹ���"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("���ڹ氡��"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("���ڹ��ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
	_chest->render();
}

shopMap::shopMap()
{
	IMAGE->addImage("��������", "images/map/ground103.bmp", 960, 576, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("�������ȼ�", "images/map/!m103.bmp", 960, 576, true, RGB(255, 0, 255));
	IMAGE->addImage("�����氡��", "images/map/Par103.bmp", 960, 576, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 364, 25, 140);//left
	_door[1].Door = RectMake(530, 0, 90, 25); //top
	_door[2].Door = RectMake(940, 310, 25, 115);//right
	_door[3].Door = RectMake(436, 560, 140, 25); //bottom
	
}

shopMap::~shopMap()
{
}

HRESULT shopMap::init()
{
	return S_OK;
}

void shopMap::release()
{
}

void shopMap::update()
{
}

void shopMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("��������"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("�����氡��"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("�������ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

statueMap::statueMap()
{
	IMAGE->addImage("�������", "images/map/statueMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("������ȼ�", "images/map/!mstatueMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("����氡��", "images/map/ParstatueMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 454, 25, 150);//left
	_door[1].Door = RectMake(482, 0, 140, 25); //top
	_door[2].Door = RectMake(1085, 450, 25, 150);//right
	_door[3].Door = RectMake(476, 940, 140, 25); //bottom
	_statue = new statue;
	_statue->add(550, 480);
}

statueMap::~statueMap()
{
}

HRESULT statueMap::init()
{
	
	return S_OK;
}

void statueMap::release()
{
	SAFE_DELETE(_statue);
}

void statueMap::update()
{
	_statue->update(bm);
}

void statueMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("�������"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("����氡��"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("������ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
	_statue->render();
}

moruMap::moruMap()
{
	IMAGE->addImage("������", "images/map/moruMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("�����ȼ�", "images/map/!mmoruMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("���氡��", "images/map/ParmoruMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 454, 25, 150);//left
	_door[1].Door = RectMake(482, 0, 140, 25); //top
	_door[2].Door = RectMake(1085, 450, 25, 150);//right
	_door[3].Door = RectMake(476, 940, 140, 25); //bottom
	_moru = new moru;
	_moru->add(550, 480);
}

moruMap::~moruMap()
{
}

HRESULT moruMap::init()
{
	
	return S_OK;
}

void moruMap::release()
{
	SAFE_DELETE(_moru);
}

void moruMap::update()
{
	_moru->update(bm);
}

void moruMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("������"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("���氡��"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("�����ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
	_moru->render();
}

stage1_Boss::stage1_Boss()
{
	IMAGE->addImage("��������", "images/map/stage1_boss.bmp", 1104, 960, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("�������ȼ�", "images/map/!mstage1_boss.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("�����氡��", "images/map/Parstage1_boss.bmp", 1104, 960, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 454, 25, 150);//left
	_door[1].Door = RectMake(482, 0, 140, 25); //top
	_door[2].Door = RectMake(1085, 450, 25, 150);//right
	_door[3].Door = RectMake(476, 940, 140, 25); //bottom
}

stage1_Boss::~stage1_Boss()
{
}

HRESULT stage1_Boss::init()
{
	return S_OK;
}

void stage1_Boss::release()
{
}

void stage1_Boss::update()
{
}

void stage1_Boss::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("��������"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("�����氡��"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("�������ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

nextStage::nextStage()
{
	IMAGE->addImage("���������", "images/map/nextStage.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("�������ȼ�", "images/map/!mnextStage.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("����������", "images/map/ParnextStage.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom
	monpos[0] = { 504,156 };
	monpos[1] = { 624,263 };
	monpos[2] = { 464,282 };
	monpos[3] = { 525,342 };
}

nextStage::~nextStage()
{
}

HRESULT nextStage::init()
{
	return S_OK;
}

void nextStage::release()
{
}

void nextStage::update()
{
}

void nextStage::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("���������"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("����������"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("�������ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}
fountainMap::fountainMap()
{

	IMAGE->addImage("�м�����", "images/map/fountainMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("�м����ȼ�", "images/map/!mfountainMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("�м��氡��", "images/map/ParfountainMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 404, 25, 70);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 358, 25, 120);//right
	_door[3].Door = RectMake(428, 655, 150, 25); //bottom
	monpos[0] = { 470,263 };
	monpos[1] = { 473,573 };
	monpos[2] = { 681,381 };
	monpos[3] = { 330,440 };
	_fountain = new fountain;
	_fountain->add(504, 362);
}

fountainMap::~fountainMap()
{
}

HRESULT fountainMap::init()
{
	
	return S_OK;
}

void fountainMap::release()
{
	SAFE_DELETE(_fountain);
}

void fountainMap::update()
{
	_fountain->update(bm);
}

void fountainMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("�м�����"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("�м��氡��"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("�м����ȼ�"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
	_fountain->render();
}
