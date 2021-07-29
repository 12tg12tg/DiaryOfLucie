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
//    //맵툴초기화 함수 호출
//    maptoolSetup();
//    _currentTile.x = 0;
//    _currentTile.y = 0;
//
//    //클릭버튼 만들어두기.
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
//    //지속클릭중일때 setMap함수 호출
//    if (InputManager->isStayKeyDown(VK_LBUTTON)) setMap();
//
//    //버튼 클릭 시 컨트롤 상태 수정.
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
//    //26일 수업본 - 세이브 로드
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
//    //왼쪽끝에서부터 타일전체이미지의 너비만큼 떨어뜨러서 출력.
//    IMAGE->render("tilemap", getMemDC(), WINSIZEX - IMAGE->findImage("tilemap")->getWidth(), 0);
//   
//    //400번 반복문
//    for (size_t i = 0; i < TILEX*TILEY; i++)
//    {
//        //현재 400개의 지형을 먼저 그리고,
//        IMAGE->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
//
//        //오브젝트를 다음으로 그려서 덮어씌움.
//        //정보가없으면 건너띄고
//        if (_tiles[i].obj == OBJECT::OBJ_NONE) continue;
//        //있으면 그리기.
//        IMAGE->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
//
//    }
//    if (_isDebug) {
//        for (size_t i = 0; i < TILEX * TILEY; i++)
//        {
//            Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
//        }       
//    }
//    //버튼상자그리기
//    showButtonAndText();
//}
//
//void mapTool::maptoolSetup()
//{
//    _ctrSelect = static_cast<int>(CTRL::CTRL_TERRAINDRAW);
//    
//    //오른쪽 샘플 맵 셋팅 (표본의 타일개수만큼 이중 반복문를 돌면서, rc와 프레임시작위치인 x, y 좌표를 저장함)
//    for (size_t i = 0; i < SAMPLETILEY; i++)    //8개돌면서
//    {
//        for (size_t j = 0; j < SAMPLETILEX; j++)    //20개돌면서 0번째타일부터 20번째타일까지 (i, j) 프레임좌표설정.
//        {
//            _sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
//            _sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;
//
//            //좌표값 설정
//            //x좌표 윈도우끝에서부터 이미지천제길이만큼 당기고 j(번째)*TILESIZE를 더하면, left
//            //left에 한번더 TILESIZE를 더하면 right
//            //i(번째)*TILESIZE가 top
//            //거기에 한번더 TILESIZE를 더하면 bottom
//            SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
//                (WINSIZEX - IMAGE->findImage("tilemap")->getWidth()) + j * TILESIZE,
//                i * TILESIZE, (WINSIZEX - IMAGE->findImage("tilemap")->getWidth()) + j * TILESIZE + TILESIZE,
//                i * TILESIZE + TILESIZE);
//        }
//    }
//    //왼쪽 찍을 타일 만들기(이중반복문돌면서 rc의 정보를 세팅)
//    for (size_t i = 0; i < TILEY; i++)  //세로20번돌면서
//    {
//        for (size_t j = 0; j < TILEX; j++)  //가로20번돌면서
//        {
//            SetRect(&_tiles[i * TILEX + j].rc,
//                j * TILESIZE,
//                i * TILESIZE,
//                j * TILESIZE + TILESIZE,
//                i * TILESIZE + TILESIZE);
//        }
//    }
//    //처음 깔려 있는 타일
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
//    //오른쪽 샘플 (20*8번 돌면서 마우스가 타일사각형 안에 있으면, 현재 타일x와 y를 샘플의 x, y 프레임으로 설정)
//    for (size_t i = 0; i < SAMPLETILEX*SAMPLETILEY; i++)
//    {
//        if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse))
//        {
//            _currentTile.x = _sampleTiles[i].terrainFrameX;
//            _currentTile.y = _sampleTiles[i].terrainFrameY;
//            break;
//        }
//    }
//    //왼쪽 타일 (20*20번 돌면서 마우스 커서가 타일 사각형 안에 있으면, 현재정보를 바탕으로 그림옮겨그림)
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
//            //그리는 상태가 아니라면 지우개 상태라 가정하고 오브젝트를 NONE으로 바꿈.
//            //이러면 다음부터 그 블럭은 오브젝트출력이안됨.
//            default:
//                _tiles[i].obj = OBJECT::OBJ_NONE;
//                break;
//            }
//            InvalidateRect(m_hWnd, NULL, false); //무효화함수
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
//    TextOut(getMemDC(), _terrain.left + (_terrain.right - _terrain.left) / 2 - 20, _terrain.top + (_terrain.bottom - _terrain.top) / 2 - 10, "지형", lstrlen("지형"));
//    TextOut(getMemDC(), _object.left + (_object.right - _object.left) / 2 - 30, _object.top + (_object.bottom - _object.top) / 2 - 10, "오브젝트", lstrlen("오브젝트"));
//    TextOut(getMemDC(), _erase.left + (_erase.right - _erase.left) / 2 - 25, _erase.top + (_erase.bottom - _erase.top) / 2 - 10, "지우기", lstrlen("지우기"));
//    TextOut(getMemDC(), _save.left + (_save.right - _save.left) / 2 - 25, _save.top + (_save.bottom - _save.top) / 2 - 10, "세이브", lstrlen("세이브"));
//    TextOut(getMemDC(), _load.left + (_load.right - _load.left) / 2 - 20, _load.top + (_load.bottom - _load.top) / 2 - 10, "로드", lstrlen("로드"));
//    SetTextColor(getMemDC(), RGB(0, 0, 255));
//    if (_ctrSelect == (int)CTRL::CTRL_TERRAINDRAW)       TextOut(getMemDC(), _terrain.left + (_terrain.right - _terrain.left) / 2 - 20, _terrain.top + (_terrain.bottom - _terrain.top) / 2 - 10, "지형", lstrlen("지형"));
//    else if (_ctrSelect == (int)CTRL::CTRL_OBJDRAW)      TextOut(getMemDC(), _object.left + (_object.right - _object.left) / 2 - 30, _object.top + (_object.bottom - _object.top) / 2 - 10, "오브젝트", lstrlen("오브젝트"));
//    else if (_ctrSelect == (int)CTRL::CTRL_ERASER)       TextOut(getMemDC(), _erase.left + (_erase.right - _erase.left) / 2 - 25, _erase.top + (_erase.bottom - _erase.top) / 2 - 10, "지우기", lstrlen("지우기"));
//    else if (_ctrSelect == (int)CTRL::CTRL_SAVE)         TextOut(getMemDC(), _save.left + (_save.right - _save.left) / 2 - 25, _save.top + (_save.bottom - _save.top) / 2 - 10, "세이브", lstrlen("세이브"));
//    else if (_ctrSelect == (int)CTRL::CTRL_LOAD)         TextOut(getMemDC(), _load.left + (_load.right - _load.left) / 2 - 20, _load.top + (_load.bottom - _load.top) / 2 - 10, "로드", lstrlen("로드"));
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
//    WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL); //타일메모리를그대로저장
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
////    //스트링벡터 돌기
////    for (size_t i = 0; i < vStr.size(); )
////    {
////        //타일 벡터 돌기
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
