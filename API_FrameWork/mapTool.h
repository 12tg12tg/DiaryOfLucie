#pragma once
#include "gameNode.h"
//#define TILESIZE 32 //������ ȭ�� Ÿ�� �ϳ��� ����(���簢��)
//#define TILEX    20 //���� ȭ�� Ÿ�� X (Ÿ�� ���� ����)
//#define TILEY    20 //���� ȭ�� Ÿ�� Y (Ÿ�� ���� ����)
//
//#define TILESIZEX TILEX * TILESIZE //Ÿ�� ��ü ���� ����
//#define TILESIZEY TILEY * TILESIZE //Ÿ�� ��ü ���� ����
//
////ȭ�� ������ �̹��� Ÿ�� ���� 
//#define SAMPLETILEX 20
//#define SAMPLETILEY 8
//
////�������� ����� ���� ��Ʈ�� ����(Ŭ���� ���� �ٲ�)
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
////���� ����
//enum class TERRAIN
//{
//	TR_CEMENT,TR_DESERT,TR_GRASS,TR_WATER,TR_END
//};
////������Ʈ(ex : ���� ���ʿ� ��ġ, �����̰ų� �μ����ų� �ϴ� ��ȭ�� �ټ��ִ� ��ü)
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
////��ġ��ǥ (????????????????????????????)
//enum class POS
//{
//	POS_FLAG1,
//	POS_FLAG2,
//	POS_TANK1,
//	POS_TANK2
//};
////���� Ÿ�� ����ü
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
////���� Ÿ�� ����ü
//struct tagSampleTile
//{
//	RECT rcTile;
//	int terrainFrameX;
//	int terrainFrameY;
//};
////���� Ÿ�� ����ü
//struct tagCurrentTile
//{
//	int x;
//	int y;
//};


//class mapTool :public gameNode
//{
//private:
//	tagCurrentTile _currentTile;							//����Ÿ����ǥ
//	tagTile _tiles[TILEX * TILEY];							//���� Ÿ�� 400�� �迭
//	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//������ Ÿ�� ǥ��������ŭ �迭. 8x20��
//
//	int _ctrSelect;											//������Ʈ�ѻ���(switch���� �̿�)
//	int _oldctr;											//���� ��Ʈ�� ����
//
//	RECT _terrain;		//������ư
//	RECT _object;		//������Ʈ��ư
//	RECT _erase;		//���찳��ư
//	RECT _save;		//���̺�
//	RECT _load;		//�ε�
//
//	//26�� ������ - ���̺�ε�
//	int _pos[2];
//
//	//���߿��߰��Ұ�(.map Ȯ���ڷ� �����ϱ�����)
//	//1.HANDLE �־����.
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
//	void maptoolSetup();		//�����ʱ�ȭ
//	void setMap();				//���ʱ�ȭ
//	void showButtonAndText();
//
//	TERRAIN terrainSelect(int frameX, int frameY);	//���������Ͽ� ��ȯ
//	OBJECT objectSelect(int frameX, int frameY);	//������Ʈ�����Ͽ� ��ȯ
//
//	//void saveData();
//	//void loadData();
//
//	//26�� ������ - ���̺�ε�
//	void save();
//	void load();
//
//	tagTile* getTiles() { return _tiles; }
//	int getTileSize() { return TILEX * TILEY; }
//	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
//};

