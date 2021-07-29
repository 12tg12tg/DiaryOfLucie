#include "framework.h"
#include "mapTool.h"
//mapTool::mapTool()
//{
//}
//
//mapTool::~mapTool()
//{
//}
//
//HRESULT mapTool::init()
//{
//    IMAGE->addFrameImage("tilemap", "images/tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);
//    
//    //�����ʱ�ȭ �Լ� ȣ��
//    maptoolSetup();
//    _currentTile.x = 0;
//    _currentTile.y = 0;
//
//    //Ŭ����ư �����α�.
//    _terrain = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2, 100, 100);
//    _object = RectMakeCenter(WINSIZEX / 2 + 250, WINSIZEY / 2, 100, 100);
//    _erase = RectMakeCenter(WINSIZEX / 2 + 400, WINSIZEY / 2, 100, 100);
//    _save = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2 + 200, 100, 100);
//    _load = RectMakeCenter(WINSIZEX / 2 + 250, WINSIZEY / 2 + 200, 100, 100);
//
//    return S_OK;
//}
//
//void mapTool::release()
//{
//}
//
//void mapTool::update()
//{
//    //����Ŭ�����϶� setMap�Լ� ȣ��
//    if (InputManager->isStayKeyDown(VK_LBUTTON)) setMap();
//
//    //��ư Ŭ�� �� ��Ʈ�� ���� ����.
//    if (PtInRect(&_terrain, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
//    {
//        _ctrSelect = static_cast<int>(CTRL::CTRL_TERRAINDRAW);
//    }
//    else if (PtInRect(&_object, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
//    {
//        _ctrSelect = static_cast<int>(CTRL::CTRL_OBJDRAW);
//    }
//    else if (PtInRect(&_erase, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
//    {
//        _ctrSelect = static_cast<int>(CTRL::CTRL_ERASER);
//    }
//    //else if (PtInRect(&_save, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
//    //{
//    //    _oldctr = _ctrSelect;
//    //    _ctrSelect = static_cast<int>(CTRL::CTRL_SAVE);
//    //}
//    //else if (PtInRect(&_load, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
//    //{
//    //    _oldctr = _ctrSelect;
//    //    _ctrSelect = static_cast<int>(CTRL::CTRL_LOAD);
//    //}
//
//    //if (_ctrSelect == (int)CTRL::CTRL_SAVE)
//    //{
//    //    _ctrSelect = _oldctr;
//    //    saveData();
//    //}
//    //if (_ctrSelect == (int)CTRL::CTRL_LOAD)
//    //{
//    //    _ctrSelect = _oldctr;
//    //    loadData();
//    //}
//
//    //26�� ������ - ���̺� �ε�
//    else if (PtInRect(&_save, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
//    {
//        save();
//    }
//    else if (PtInRect(&_load, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
//    {
//        load();
//    }
//}
//
//void mapTool::render()
//{
//    //���ʳ��������� Ÿ����ü�̹����� �ʺ�ŭ ����߷��� ���.
//    IMAGE->render("tilemap", getMemDC(), WINSIZEX - IMAGE->findImage("tilemap")->getWidth(), 0);
//   
//    //400�� �ݺ���
//    for (size_t i = 0; i < TILEX*TILEY; i++)
//    {
//        //���� 400���� ������ ���� �׸���,
//        IMAGE->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
//
//        //������Ʈ�� �������� �׷��� �����.
//        //������������ �ǳʶ��
//        if (_tiles[i].obj == OBJECT::OBJ_NONE) continue;
//        //������ �׸���.
//        IMAGE->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
//
//    }
//    if (_isDebug) {
//        for (size_t i = 0; i < TILEX * TILEY; i++)
//        {
//            Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
//        }       
//    }
//    //��ư���ڱ׸���
//    showButtonAndText();
//}
//
//void mapTool::maptoolSetup()
//{
//    _ctrSelect = static_cast<int>(CTRL::CTRL_TERRAINDRAW);
//    
//    //������ ���� �� ���� (ǥ���� Ÿ�ϰ�����ŭ ���� �ݺ����� ���鼭, rc�� �����ӽ�����ġ�� x, y ��ǥ�� ������)
//    for (size_t i = 0; i < SAMPLETILEY; i++)    //8�����鼭
//    {
//        for (size_t j = 0; j < SAMPLETILEX; j++)    //20�����鼭 0��°Ÿ�Ϻ��� 20��°Ÿ�ϱ��� (i, j) ��������ǥ����.
//        {
//            _sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
//            _sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;
//
//            //��ǥ�� ����
//            //x��ǥ �����쳡�������� �̹���õ�����̸�ŭ ���� j(��°)*TILESIZE�� ���ϸ�, left
//            //left�� �ѹ��� TILESIZE�� ���ϸ� right
//            //i(��°)*TILESIZE�� top
//            //�ű⿡ �ѹ��� TILESIZE�� ���ϸ� bottom
//            SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
//                (WINSIZEX - IMAGE->findImage("tilemap")->getWidth()) + j * TILESIZE,
//                i * TILESIZE, (WINSIZEX - IMAGE->findImage("tilemap")->getWidth()) + j * TILESIZE + TILESIZE,
//                i * TILESIZE + TILESIZE);
//        }
//    }
//    //���� ���� Ÿ�� �����(���߹ݺ������鼭 rc�� ������ ����)
//    for (size_t i = 0; i < TILEY; i++)  //����20�����鼭
//    {
//        for (size_t j = 0; j < TILEX; j++)  //����20�����鼭
//        {
//            SetRect(&_tiles[i * TILEX + j].rc,
//                j * TILESIZE,
//                i * TILESIZE,
//                j * TILESIZE + TILESIZE,
//                i * TILESIZE + TILESIZE);
//        }
//    }
//    //ó�� ��� �ִ� Ÿ��
//    for (size_t i = 0; i < TILEX*TILEY; i++)
//    {
//        _tiles[i].terrainFrameX = 3;
//        _tiles[i].terrainFrameY = 0;
//
//        _tiles[i].objFrameX = 0;
//        _tiles[i].objFrameY = 0;
//
//        _tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
//        _tiles[i].obj = OBJECT::OBJ_NONE;
//    }
//}
//
//void mapTool::setMap()
//{
//    //������ ���� (20*8�� ���鼭 ���콺�� Ÿ�ϻ簢�� �ȿ� ������, ���� Ÿ��x�� y�� ������ x, y ���������� ����)
//    for (size_t i = 0; i < SAMPLETILEX*SAMPLETILEY; i++)
//    {
//        if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse))
//        {
//            _currentTile.x = _sampleTiles[i].terrainFrameX;
//            _currentTile.y = _sampleTiles[i].terrainFrameY;
//            break;
//        }
//    }
//    //���� Ÿ�� (20*20�� ���鼭 ���콺 Ŀ���� Ÿ�� �簢�� �ȿ� ������, ���������� �������� �׸��Űܱ׸�)
//    for (size_t i = 0; i < TILEX*TILEY; i++)
//    {
//        if (PtInRect(&_tiles[i].rc, m_ptMouse))
//        {
//            switch ((CTRL)_ctrSelect)
//            {
//
//            case CTRL::CTRL_TERRAINDRAW:
//            {
//                _tiles[i].terrainFrameX = _currentTile.x;
//                _tiles[i].terrainFrameY = _currentTile.y;
//                _tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
//            }
//            break;
//            case CTRL::CTRL_OBJDRAW:
//            {
//                _tiles[i].objFrameX = _currentTile.x;
//                _tiles[i].objFrameY = _currentTile.y;
//                _tiles[i].obj = objectSelect(_currentTile.x, _currentTile.y);
//            }
//            break;
//            //�׸��� ���°� �ƴ϶�� ���찳 ���¶� �����ϰ� ������Ʈ�� NONE���� �ٲ�.
//            //�̷��� �������� �� ���� ������Ʈ����̾ȵ�.
//            default:
//                _tiles[i].obj = OBJECT::OBJ_NONE;
//                break;
//            }
//            InvalidateRect(m_hWnd, NULL, false); //��ȿȭ�Լ�
//            break;
//        }
//    }
//}
//
//void mapTool::showButtonAndText()
//{
//    Rectangle(getMemDC(), _terrain.left, _terrain.top, _terrain.right, _terrain.bottom);
//    Rectangle(getMemDC(), _object.left, _object.top, _object.right, _object.bottom);
//    Rectangle(getMemDC(), _erase.left, _erase.top, _erase.right, _erase.bottom);
//    Rectangle(getMemDC(), _save.left, _save.top, _save.right, _save.bottom);
//    Rectangle(getMemDC(), _load.left, _load.top, _load.right, _load.bottom);
//    TextOut(getMemDC(), _terrain.left + (_terrain.right - _terrain.left) / 2 - 20, _terrain.top + (_terrain.bottom - _terrain.top) / 2 - 10, "����", lstrlen("����"));
//    TextOut(getMemDC(), _object.left + (_object.right - _object.left) / 2 - 30, _object.top + (_object.bottom - _object.top) / 2 - 10, "������Ʈ", lstrlen("������Ʈ"));
//    TextOut(getMemDC(), _erase.left + (_erase.right - _erase.left) / 2 - 25, _erase.top + (_erase.bottom - _erase.top) / 2 - 10, "�����", lstrlen("�����"));
//    TextOut(getMemDC(), _save.left + (_save.right - _save.left) / 2 - 25, _save.top + (_save.bottom - _save.top) / 2 - 10, "���̺�", lstrlen("���̺�"));
//    TextOut(getMemDC(), _load.left + (_load.right - _load.left) / 2 - 20, _load.top + (_load.bottom - _load.top) / 2 - 10, "�ε�", lstrlen("�ε�"));
//    SetTextColor(getMemDC(), RGB(0, 0, 255));
//    if (_ctrSelect == (int)CTRL::CTRL_TERRAINDRAW)       TextOut(getMemDC(), _terrain.left + (_terrain.right - _terrain.left) / 2 - 20, _terrain.top + (_terrain.bottom - _terrain.top) / 2 - 10, "����", lstrlen("����"));
//    else if (_ctrSelect == (int)CTRL::CTRL_OBJDRAW)      TextOut(getMemDC(), _object.left + (_object.right - _object.left) / 2 - 30, _object.top + (_object.bottom - _object.top) / 2 - 10, "������Ʈ", lstrlen("������Ʈ"));
//    else if (_ctrSelect == (int)CTRL::CTRL_ERASER)       TextOut(getMemDC(), _erase.left + (_erase.right - _erase.left) / 2 - 25, _erase.top + (_erase.bottom - _erase.top) / 2 - 10, "�����", lstrlen("�����"));
//    else if (_ctrSelect == (int)CTRL::CTRL_SAVE)         TextOut(getMemDC(), _save.left + (_save.right - _save.left) / 2 - 25, _save.top + (_save.bottom - _save.top) / 2 - 10, "���̺�", lstrlen("���̺�"));
//    else if (_ctrSelect == (int)CTRL::CTRL_LOAD)         TextOut(getMemDC(), _load.left + (_load.right - _load.left) / 2 - 20, _load.top + (_load.bottom - _load.top) / 2 - 10, "�ε�", lstrlen("�ε�"));
//    SetTextColor(getMemDC(), BLACKNESS);
//}
//
//TERRAIN mapTool::terrainSelect(int frameX, int frameY)
//{
//    if (frameX == 1 && frameY == 0) return TERRAIN::TR_CEMENT;
//    else if (frameX == 2 && frameY == 0) return TERRAIN::TR_DESERT;
//    else if (frameX == 3 && frameY == 0) return TERRAIN::TR_GRASS;
//    else if (frameX == 4 && frameY == 0) return TERRAIN::TR_WATER;
//    else if (frameX == 5 && frameY == 0) return TERRAIN::TR_GRASS;
//    else if (frameX == 6 && frameY == 0) return TERRAIN::TR_WATER;
//    else if (frameX == 7 && frameY == 0) return TERRAIN::TR_CEMENT;
//    else if (frameX == 8 && frameY == 0) return TERRAIN::TR_DESERT;
//    else if (frameX == 9 && frameY == 0) return TERRAIN::TR_GRASS;
//    else if (frameX == 10 && frameY == 0) return TERRAIN::TR_GRASS;
//    else if (frameX == 0 && frameY == 1) return TERRAIN::TR_WATER;
//
//
//
//
//    return TERRAIN::TR_GRASS;
//}
//
//OBJECT mapTool::objectSelect(int frameX, int frameY)
//{
//    if (frameX == 0 && frameY == 0)
//    {
//        return OBJECT::OBJ_TANK1;
//    }
//    else if (frameX == 0 && frameY == 8)
//    {
//        return OBJECT::OBJ_TANK2;
//    }
//    else if (frameX == 0 && frameY == 1)
//    {
//        return OBJECT::OBJ_BLOCK1;
//    }
//    else if (frameX == 0 && frameY == 2)
//    {
//        return OBJECT::OBJ_BLOCK3;
//    }
//    else if (frameX == 0 && frameY == 3)
//    {
//        return OBJECT::OBJ_BLOCKS;
//    }
//
//
//
//
//
//
//    return OBJECT::OBJ_BLOCK1;
//}
//
//void mapTool::save()
//{
//    HANDLE file;
//    DWORD write;
//
//    file = CreateFile("tileMap.map",
//        GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL); //Ÿ�ϸ޸𸮸��״������
//    WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);
//    CloseHandle(file);
//}
//
//void mapTool::load()
//{
//    HANDLE file;
//    DWORD read;
//
//    file = CreateFile("tileMap.map",
//        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//    ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
//    ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
//    CloseHandle(file);
//}
//
////void mapTool::saveData()
////{
////    char temp[64];
////    vector<string> vStr;
////    for (size_t i = 0; i < TILEX * TILEY; i++)
////    {
////        vStr.push_back(_itoa(int(_tiles[i].obj), temp, 10));
////        vStr.push_back(_itoa(_tiles[i].objFrameX, temp, 10));
////        vStr.push_back(_itoa(_tiles[i].objFrameY, temp, 10));
////        vStr.push_back(_itoa(int(_tiles[i].terrain), temp, 10));
////        vStr.push_back(_itoa(_tiles[i].terrainFrameX, temp, 10));
////        vStr.push_back(_itoa(_tiles[i].terrainFrameY, temp, 10));
////    }
////    TXT->txtSave("save/tileMap.txt", vStr);
////}
////
////void mapTool::loadData()
////{
////    vector<string> vStr(TXT->txtLoad("save/tileMap.txt"));
////
////    //��Ʈ������ ����
////    for (size_t i = 0; i < vStr.size(); )
////    {
////        //Ÿ�� ���� ����
////        for (size_t j = 0; j < TILEX*TILEY; j++, i+=6)
////        {
////            _tiles[j].obj = (OBJECT)stoi(vStr[i]);
////            _tiles[j].objFrameX = stoi(vStr[i+1]);
////            _tiles[j].objFrameY = stoi(vStr[i+2]);
////            _tiles[j].terrain = (TERRAIN)stoi(vStr[i+3]);
////            _tiles[j].terrainFrameX = stoi(vStr[i+4]);
////            _tiles[j].terrainFrameY = stoi(vStr[i+5]);
////        }
////    }
////}
