#pragma once
#include "gameNode.h"
//#define TILESIZE 32 //오른쪽 화면 타일 하나의 길이(정사각형)
//#define TILEX    20 //왼쪽 화면 타일 X (타일 가로 개수)
//#define TILEY    20 //왼쪽 화면 타일 Y (타일 세로 개수)
//
//#define TILESIZEX TILEX * TILESIZE //타일 전체 가로 길이
//#define TILESIZEY TILEY * TILESIZE //타일 전체 세로 길이
//
////화면 오른쪽 이미지 타일 갯수 
//#define SAMPLETILEX 20
//#define SAMPLETILEY 8
//
////맵툴에서 사용할 현재 컨트롤 상태(클릭을 통해 바뀜)
//enum class CTRL
//{
//	CTRL_SAVE,
//	CTRL_LOAD,
//	CTRL_TERRAINDRAW,
//	CTRL_OBJDRAW,
//	CTRL_ERASER,
//	CTRL_MAP1,
//	CTRL_MAP2,
//	CTRL_END
//};
////지형 종류
//enum class TERRAIN
//{
//	TR_CEMENT,TR_DESERT,TR_GRASS,TR_WATER,TR_END
//};
////오브젝트(ex : 지형 위쪽에 배치, 움직이거나 부서지거나 하는 변화를 줄수있는 물체)
//enum class OBJECT
//{
//	OBJ_BLOCK1,
//	OBJ_BLOCK3,
//	OBJ_BLOCKS,
//	OBJ_FLAG1,
//	OBJ_FLAG2,
//	OBJ_TANK1,
//	OBJ_TANK2,
//	OBJ_NONE
//};
////위치좌표 (????????????????????????????)
//enum class POS
//{
//	POS_FLAG1,
//	POS_FLAG2,
//	POS_TANK1,
//	POS_TANK2
//};
////찍을 타일 구조체
//struct tagTile
//{
//	TERRAIN terrain;
//	OBJECT obj;
//	RECT rc;
//
//	int terrainFrameX;
//	int terrainFrameY;
//	int objFrameX;
//	int objFrameY;
//
//};
////샘플 타일 구조체
//struct tagSampleTile
//{
//	RECT rcTile;
//	int terrainFrameX;
//	int terrainFrameY;
//};
////현재 타일 구조체
//struct tagCurrentTile
//{
//	int x;
//	int y;
//};


//class mapTool :public gameNode
//{
//private:
//	tagCurrentTile _currentTile;							//현재타일좌표
//	tagTile _tiles[TILEX * TILEY];							//왼쪽 타일 400개 배열
//	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//오른쪽 타일 표본개수만큼 배열. 8x20개
//
//	int _ctrSelect;											//현재컨트롤상태(switch문에 이용)
//	int _oldctr;											//이전 컨트롤 상태
//
//	RECT _terrain;		//지형버튼
//	RECT _object;		//오브젝트버튼
//	RECT _erase;		//지우개버튼
//	RECT _save;		//세이브
//	RECT _load;		//로드
//
//	//26일 수업본 - 세이브로드
//	int _pos[2];
//
//	//나중에추가할것(.map 확장자로 저장하기위해)
//	//1.HANDLE 있어야함.
//
//
//	bool _isDebug;
//public:
//	mapTool();
//	~mapTool();
//
//	HRESULT init();
//	void release();
//	void update();
//	void render();
//
//	void maptoolSetup();		//맵툴초기화
//	void setMap();				//맵초기화
//	void showButtonAndText();
//
//	TERRAIN terrainSelect(int frameX, int frameY);	//지형선택하여 반환
//	OBJECT objectSelect(int frameX, int frameY);	//오브젝트선택하여 반환
//
//	//void saveData();
//	//void loadData();
//
//	//26일 수업본 - 세이브로드
//	void save();
//	void load();
//
//	tagTile* getTiles() { return _tiles; }
//	int getTileSize() { return TILEX * TILEY; }
//	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
//};

