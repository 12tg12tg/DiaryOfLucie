#include "framework.h"
#include "Cmap.h"

Cmap::Cmap()
{
	IMAGE->addImage("95배경", "images/map/ground95.bmp", 1104,960, true, RGB(255, 0, 255));
	_collisionMap =IMAGE->addImage("95픽셀", "images/map/!m95.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("95가림", "images/map/par95.bmp", 1104, 960, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0,454, 25, 150);//left
	_door[1].Door = RectMake(482, 0, 140, 25); //top
	_door[2].Door = RectMake(1085, 450, 25 , 150);//right
	_door[3].Door = RectMake(476, 940,140, 25); //bottom
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
	

	ZORDER->ZorderRender(IMAGE->findImage("95배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("95가림"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("95픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
	
}

Cmap2::Cmap2()
{
	IMAGE->addImage("57배경", "images/map/ground57.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("57픽셀", "images/map/!m57.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("57가림", "images/map/par57.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 404 , 25, 70);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 358,25 , 120);//right
	_door[3].Door = RectMake(428, 655,150, 25); //bottom
}

Cmap2::~Cmap2()
{
}

HRESULT Cmap2::init()
{
	monpos[0] = { 445,570 };
	monpos[1] = { 624,263 };
	monpos[2] = { 464,282 };
	monpos[3] = { 525,342 };
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

	ZORDER->ZorderRender(IMAGE->findImage("57배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("57가림"), ZABOVEMAP, WINSIZEX, 0, 0);

	if(_isDebug) ZORDER->ZorderRender(IMAGE->findImage("57픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door,ZEFFECT1);
}

Cmap3::Cmap3()
{
	IMAGE->addImage("104배경", "images/map/ground104.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("104픽셀", "images/map/!m104.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("104가림", "images/map/par104.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0,333, 20,100);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 321, 25,110 );//right
	_door[3].Door = RectMake(434, 754, 140, 25); //bottom
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
	
	
	ZORDER->ZorderRender(IMAGE->findImage("104배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("104가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if(_isDebug) ZORDER->ZorderRender(IMAGE->findImage("104픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}
	

Cmap4::Cmap4()
{
	IMAGE->addImage("105배경", "images/map/ground105.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("105픽셀", "images/map/!m105.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("105가림", "images/map/par105.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 268, 25,160);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 333 , 25, 100);//right
	_door[3].Door = RectMake(433, 750, 145, 25); //bottom
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

	ZORDER->ZorderRender(IMAGE->findImage("105배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("105가림"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("105픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door,ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door,ZEFFECT1);
}

Cmap5::Cmap5()
{
	IMAGE->addImage("115배경", "images/map/ground115.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("115픽셀", "images/map/!m115.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("115가림", "images/map/par115.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 353, 25,150);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 356, 25, 140);//right
	_door[3].Door = RectMake(428,650 , 150, 25); //bottom
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


	ZORDER->ZorderRender(IMAGE->findImage("115배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("115가림"), ZABOVEMAP, WINSIZEX, 0, 0);

	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("115픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap6::Cmap6()
{
	IMAGE->addImage("50배경", "images/map/ground50.bmp", 1008, 768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("50픽셀", "images/map/!m50.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("50가림", "images/map/par50.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 312, 25, 130);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 303, 25, 130);//right
	_door[3].Door = RectMake(430, 750, 150, 25); //bottom
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
	ZORDER->ZorderRender(IMAGE->findImage("50배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("50가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("50픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap7::Cmap7()
{
	IMAGE->addImage("51배경", "images/map/ground51.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("51픽셀", "images/map/!m51.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("51가림", "images/map/par51.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 404, 25, 70);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(985, 358, 25, 120);//right
	_door[3].Door = RectMake(428, 655, 150, 25); //bottom
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
	ZORDER->ZorderRender(IMAGE->findImage("51배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("51가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("51픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap8::Cmap8()
{
	IMAGE->addImage("100배경", "images/map/ground100.bmp", 1008,768, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("100픽셀", "images/map/!m100.bmp", 1008, 768, true, RGB(255, 0, 255));
	IMAGE->addImage("100가림", "images/map/par100.bmp", 1008, 768, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 312, 25, 130);//left
	_door[1].Door = RectMake(432, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 303, 25, 130);//right
	_door[3].Door = RectMake(430, 750, 150, 25); //bottom
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
	ZORDER->ZorderRender(IMAGE->findImage("100배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("100가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("100픽셀"), ZCOLMAP, WINSIZEY, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap9::Cmap9()
{
	IMAGE->addImage("108배경", "images/map/ground108.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("108픽셀", "images/map/!m108.bmp", 1008, 672 , true, RGB(255, 0, 255));
	IMAGE->addImage("108가림", "images/map/par108.bmp", 1008, 672 , true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433,0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650,160,25); //bottom
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
	ZORDER->ZorderRender(IMAGE->findImage("108배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("108가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("108픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

Cmap10::Cmap10()
{
	IMAGE->addImage("114배경", "images/map/ground114.bmp", 1108,672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("114픽셀", "images/map/!m114.bmp", 1108, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("114가림", "images/map/par114.bmp", 1108, 672, true, RGB(255, 0, 255));
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
	summonMon(4);

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
	ZORDER->ZorderRender(IMAGE->findImage("114배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("114가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("114픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

chestMap::chestMap()
{
	IMAGE->addImage("상자방배경", "images/map/chestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("상자방픽셀", "images/map/!mchestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	IMAGE->addImage("상자방가림", "images/map/parchestMap.bmp", 1008, 672, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 355, 25, 120);//left
	_door[1].Door = RectMake(433, 0, 140, 25); //top
	_door[2].Door = RectMake(990, 355, 25, 120);//right
	_door[3].Door = RectMake(427, 650, 160, 25); //bottom
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
}

void chestMap::update()
{
}

void chestMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("상자방배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("상자방가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("상자방픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

shopMap::shopMap()
{
	IMAGE->addImage("상점방배경", "images/map/ground103.bmp", 960, 576, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("상점방픽셀", "images/map/!m103.bmp", 960, 576, true, RGB(255, 0, 255));
	IMAGE->addImage("상점방가림", "images/map/par103.bmp", 960, 576, true, RGB(255, 0, 255));
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
	ZORDER->ZorderRender(IMAGE->findImage("상점방배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("상점방가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("상점방픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

statueMap::statueMap()
{
	IMAGE->addImage("석상방배경", "images/map/statueMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("석상방픽셀", "images/map/!mstatueMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("석상방가림", "images/map/parstatueMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 454, 25, 150);//left
	_door[1].Door = RectMake(482, 0, 140, 25); //top
	_door[2].Door = RectMake(1085, 450, 25, 150);//right
	_door[3].Door = RectMake(476, 940, 140, 25); //bottom
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
}

void statueMap::update()
{
}

void statueMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("석상방배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("석상방가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("석상방픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}

moruMap::moruMap()
{
	IMAGE->addImage("모루방배경", "images/map/moruMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	_collisionMap = IMAGE->addImage("모루방픽셀", "images/map/!mmoruMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	IMAGE->addImage("모루방가림", "images/map/parmoruMap.bmp", 1104, 960, true, RGB(255, 0, 255));
	_door[0].Door = RectMake(0, 454, 25, 150);//left
	_door[1].Door = RectMake(482, 0, 140, 25); //top
	_door[2].Door = RectMake(1085, 450, 25, 150);//right
	_door[3].Door = RectMake(476, 940, 140, 25); //bottom
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
}

void moruMap::update()
{
}

void moruMap::render()
{
	ZORDER->ZorderRender(IMAGE->findImage("모루방배경"), ZFLOORMAP, WINSIZEX, 0, 0);
	ZORDER->ZorderRender(IMAGE->findImage("모루방가림"), ZABOVEMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRender(IMAGE->findImage("모루방픽셀"), ZCOLMAP, WINSIZEX, 0, 0);
	if (_isDebug)ZORDER->ZorderRectangle(_door[0].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[1].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[2].Door, ZEFFECT1);
	if (_isDebug)ZORDER->ZorderRectangle(_door[3].Door, ZEFFECT1);
}
