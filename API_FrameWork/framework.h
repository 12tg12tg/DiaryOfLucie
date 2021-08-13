// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


using namespace std;

//=======================//
//			STL			//
//=====================//
#include<map>
#include<vector>
#include <string>
#include <algorithm>

//=======================//
//	내가만든 헤더파일		//
//=====================//
#include"utils.h"
#include"commonMacroFunction.h"
#include"Input.h"
#include"imageManager.h"
#include"timeManager.h"
#include"sceneManager.h"
#include"soundManager.h"
#include"animationManager.h"
#include"effectManager.h"
#include"randomFunction.h"
#include"txtData.h"
#include"OBBCollision.h"
#include"Zorder.h"
#include"Cplayer.h"
#include"CplayerData.h"

//=======================//
//		Manager			//
//=====================//
#define InputManager	Input::getSingleton()
#define INPUT			Input::getSingleton()
#define RND				RandomFunction::getSingleton()
#define IMAGE			imageManager::getSingleton()
#define TIME			timeManager::getSingleton()
#define TXT				txtData::getSingleton()
#define SCENE			SceneManager::getSingleton()
#define SOUND			soundManager::getSingleton()
#define ANIMATION		animationManager::getSingleton()
#define EFFECT			effectManager::getSingleton()
#define OBB				OBBCollision::getSingleton()
#define ZORDER			Zorder::getSingleton()

#define PLAYER			Cplayer::getSingleton()
#define PLAYERDATA		CplayerDate::getSingleton()
//===================//
//	매크로 설정부분	//
//=================//

#define WINNAME			(LPTSTR)(TEXT("루시의 일기"))
#define WINSTARTX		50//시작점
#define WINSTARTY		50
//#define WINSIZEX		1500
//#define WINSIZEX		640
#define WINSIZEX		1024
#define WINSIZEY		768
//#define WINSIZEY		640
#define WINSTYLE		WS_CAPTION | WS_SYSMENU


//===========================//
//	메인게임 릴리즈에서 사용	//
//=========================//

#define SAFE_DELETE(p) {if(p) {delete p; (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = NULL;}}


//===============================================//
//	전역변수 (인스턴스, 윈도우 핸들, 마우스 좌표)	//
//=============================================//

extern HINSTANCE m_hInstance;
extern HWND m_hWnd;
extern POINT m_ptMouse;