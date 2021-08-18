#include"framework.h"
#include "image.h"
//알파블렌드를 사용하기 위해
#pragma comment(lib, "msimg32.lib")

image::image() :	_imageInfo(NULL),
					_fileName(NULL),
					_isTrans(false),
					_transColor(RGB(0, 0, 0))
{
}
image::~image()
{
}

HRESULT image::init(const int width, const int height)
{
	//이미지 정보가 들어있으면 해제하라.
	if (_imageInfo != NULL) release();

	//DC가져오기(현재 윈도우에 대한 화면 DC를 임시로 가져옴)
	HDC hdc = GetDC(m_hWnd);

	//CreateCompatibleDC : 비트맵을 출력하기 위해서 메모리DC를 만들어준다.
	//CreateCompatibleBitmap : 원본DC와 호환되는 비트맵 생성.
	
	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //비트맵출력을위해메모리dc를 만들어주는 함수.
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //원본dc와 호환되는 비트맵을 만듬.
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 이름 초기화
	_fileName = NULL;


	//투명키 셋팅
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const int width, const int height, COLORREF color)
{
	//이미지 정보가 들어있으면 해제하라.
	if (_imageInfo != NULL) release();

	//DC가져오기(현재 윈도우에 대한 화면 DC를 임시로 가져옴)
	HDC hdc = GetDC(m_hWnd);

	//CreateCompatibleDC : 비트맵을 출력하기 위해서 메모리DC를 만들어준다.
	//CreateCompatibleBitmap : 원본DC와 호환되는 비트맵 생성.

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //비트맵출력을위해메모리dc를 만들어주는 함수.
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //원본dc와 호환되는 비트맵을 만듬.
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 이름 초기화
	_fileName = NULL;

	//투명키 셋팅
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);

	BitBlt(_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, 0, 0, BLACKNESS);
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oBrush = (HBRUSH)SelectObject(_imageInfo->hMemDC, hBrush);
	ExtFloodFill(_imageInfo->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
	SelectObject(_imageInfo->hMemDC, oBrush);
	DeleteObject(hBrush);

	return S_OK;
}

HRESULT image::init(const char* fileName, const int width, const int height, bool isTrans, COLORREF transColor)
{

	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
											fileName,
											IMAGE_BITMAP, 
											width, height, 
											LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	//파일이름
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);




	return S_OK;
}

HRESULT image::init(const char* fileName, const float x, const float y, const int width, const int height, bool isTrans, COLORREF transColor)
{
	//이게언제부터있었지?
	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;


	//파일이름
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);
	return S_OK;
}


HRESULT image::init(const char* fileName, const int width, const int height, const int frameX, const int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;


	//파일이름
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;


	//파일이름
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForRotate()
{
	HDC hdc = GetDC(m_hWnd);
	
	int size;
	if (_imageInfo->maxFrameX == 0 && _imageInfo->maxFrameY == 0) {
		size = sqrt((_imageInfo->width) * (_imageInfo->width) + (_imageInfo->height) * (_imageInfo->height));

		_rotateImage = new IMAGE_INFO;
		_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
		_imageInfo->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}
	else {
		size = sqrt((_imageInfo->frameWidth) * (_imageInfo->frameWidth) + (_imageInfo->frameHeight) * (_imageInfo->frameHeight));

		_rotateImage = new IMAGE_INFO;
		_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
		_imageInfo->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForAlphaBlend()
{
	HDC hdc = GetDC(m_hWnd);
	int size;
	if (_imageInfo->maxFrameX == 0 && _imageInfo->maxFrameY == 0) {
		size = sqrt((_imageInfo->width) * (_imageInfo->width) + (_imageInfo->height) * (_imageInfo->height));

		//알파 블렌드 옵션
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER; //블렌딩 연산자


		//알파 블렌드 사용하기 위한 이미지 초기화
		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = size;
		_blendImage->height = size;
	}
	else {
		size = sqrt((_imageInfo->frameWidth) * (_imageInfo->frameWidth) + (_imageInfo->frameHeight) * (_imageInfo->frameHeight));

		//알파 블렌드 옵션
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER; //블렌딩 연산자


		//알파 블렌드 사용하기 위한 이미지 초기화
		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = size;
		_blendImage->height = size;
	}
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForStretch()
{
	HDC hdc = GetDC(m_hWnd);

	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX*5, WINSIZEY*5);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);

	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForStretch(int x, int y)
{
	HDC hdc = GetDC(m_hWnd);

	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, x, y);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = x;
	_stretchImage->height = y;

	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

void image::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_isTrans = false;
		_transColor = RGB(0, 0, 0);

	}
	//알파블렌드 이미지 정보가 있다면 해제
	if (_blendImage)
	{
		//이미지 삭제
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_blendImage);
	}
	//로테이트정보 삭제
	if (_rotateImage)
	{
		//이미지 삭제
		SelectObject(_rotateImage->hMemDC, _rotateImage->hOBit);
		DeleteObject(_rotateImage->hBit);
		DeleteDC(_rotateImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_rotateImage);
	}
	if (_stretchImage)
	{
		//이미지 삭제
		SelectObject(_stretchImage->hMemDC, _stretchImage->hOBit);
		DeleteObject(_stretchImage->hBit);
		DeleteDC(_stretchImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_stretchImage);
	}
}

void image::render(HDC hdc)
{
	if (_isTrans)
	{
		//Gdi가 비트맵파일을 불러올때 특정 색상을 제외하고 복사해주는 함수.
		GdiTransparentBlt(
			hdc,						//복사될 장소의 DC
			_imageInfo->x,							//복사될 좌표의 시작점x
			_imageInfo->y,							//복사될 좌표의 시작점y
			_imageInfo->width,			//복사될 이미지의 가로크기
			_imageInfo->height,			//복사될 이미지의 세로크기
			_imageInfo->hMemDC,			//복사될 대상 DC
			0,							//복사 시작 지점의 x
			0,							//복사 시작 지점의 y
			_imageInfo->width,			//복사영역 가로 크기
			_imageInfo->height,			//복사영역 세로 크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속 복사.
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY); 
	}
}

void image::render(HDC hdc, const int destX, const int destY)
{
	if (_isTrans)
	{
		//Gdi가 비트맵파일을 불러올때 특정 색상을 제외하고 복사해주는 함수.
		GdiTransparentBlt(
			hdc,						//복사될 장소의 DC
			destX,							//복사될 좌표의 시작점x
			destY,							//복사될 좌표의 시작점y
			_imageInfo->width,			//복사될 이미지의 가로크기
			_imageInfo->height,			//복사될 이미지의 세로크기
			_imageInfo->hMemDC,			//복사될 대상 DC
			0,							//복사 시작 지점의 x
			0,							//복사 시작 지점의 y
			_imageInfo->width,			//복사영역 가로 크기
			_imageInfo->height,			//복사영역 세로 크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속 복사.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
//void image::★★★(HDC hdc, const int destX, const int destY, int plusSize)
//{
//	if (_isTrans)
//	{
//		//Gdi가 비트맵파일을 불러올때 특정 색상을 제외하고 복사해주는 함수.
//		GdiTransparentBlt(
//			hdc,						//복사될 장소의 DC
//			destX,							//복사될 좌표의 시작점x
//			destY,							//복사될 좌표의 시작점y
//			_imageInfo->width + plusSize,			//복사될 이미지의 가로크기
//			_imageInfo->height + plusSize,			//복사될 이미지의 세로크기
//			_imageInfo->hMemDC,			//복사될 대상 DC
//			0,							//복사 시작 지점의 x
//			0,							//복사 시작 지점의 y
//			_imageInfo->width,			//복사영역 가로 크기
//			_imageInfo->height,			//복사영역 세로 크기
//			_transColor);
//	}
//	else {
//		//BitBlt : DC영역끼리 고속 복사.
//		BitBlt(hdc, destX, destY, _imageInfo->width + plusSize, _imageInfo->height + plusSize,
//			_imageInfo->hMemDC, 0, 0, SRCCOPY);
//	}
//}
void image::render(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourheight)
{
	if (_isTrans)
	{
		//Gdi가 비트맵파일을 불러올때 특정 색상을 제외하고 복사해주는 함수.
		GdiTransparentBlt(
			hdc,						//복사될 장소의 DC
			destX,							//복사될 좌표의 시작점x
			destY,							//복사될 좌표의 시작점y
			sourWidth,			//복사될 이미지의 가로크기
			sourheight,			//복사될 이미지의 세로크기
			_imageInfo->hMemDC,			//복사될 대상 DC
			sourX,							//복사 시작 지점의 x
			sourY,							//복사 시작 지점의 y
			sourWidth,			//복사영역 가로 크기
			sourheight,			//복사영역 세로 크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속 복사.
		BitBlt(hdc, destX, destY, sourWidth, sourheight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc)
{
	if (_isTrans)
	{
		//Gdi가 비트맵파일을 불러올때 특정 색상을 제외하고 복사해주는 함수.
		GdiTransparentBlt(
			hdc,												//복사될 장소의 DC
			_imageInfo->x,												//복사될 좌표의 시작점x
			_imageInfo->y,												//복사될 좌표의 시작점y
			_imageInfo->frameWidth,								//복사될 이미지의 가로크기
			_imageInfo->frameHeight,							//복사될 이미지의 세로크기
			_imageInfo->hMemDC,									//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	//복사 시작 지점의 x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//복사 시작 지점의 y
			_imageInfo->frameWidth,								//복사영역 가로 크기
			_imageInfo->frameHeight,							//복사영역 세로 크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속 복사.
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, const int destX, const int destY)
{
	if (_isTrans)
	{
		//Gdi가 비트맵파일을 불러올때 특정 색상을 제외하고 복사해주는 함수.
		GdiTransparentBlt(
			hdc,												//복사될 장소의 DC
			destX,												//복사될 좌표의 시작점x
			destY,												//복사될 좌표의 시작점y
			_imageInfo->frameWidth,								//복사될 이미지의 가로크기
			_imageInfo->frameHeight,							//복사될 이미지의 세로크기
			_imageInfo->hMemDC,									//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	//복사 시작 지점의 x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//복사 시작 지점의 y
			_imageInfo->frameWidth,								//복사영역 가로 크기
			_imageInfo->frameHeight,							//복사영역 세로 크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속 복사.
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

//void image::☆☆☆(HDC hdc, const int destX, const int destY, int plusSize)
//{
//	if (_isTrans)
//	{
//		//Gdi가 비트맵파일을 불러올때 특정 색상을 제외하고 복사해주는 함수.
//		GdiTransparentBlt(
//			hdc,												//복사될 장소의 DC
//			destX,												//복사될 좌표의 시작점x
//			destY,												//복사될 좌표의 시작점y
//			_imageInfo->frameWidth + plusSize,					//복사될 이미지의 가로크기
//			_imageInfo->frameHeight + plusSize,					//복사될 이미지의 세로크기
//			_imageInfo->hMemDC,									//복사될 대상 DC
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,	//복사 시작 지점의 x
//			_imageInfo->currentFrameY * _imageInfo->frameHeight,//복사 시작 지점의 y
//			_imageInfo->frameWidth,								//복사영역 가로 크기
//			_imageInfo->frameHeight,							//복사영역 세로 크기
//			_transColor);
//	}
//	else {
//		//BitBlt : DC영역끼리 고속 복사.
//		BitBlt(hdc, destX, destY, _imageInfo->frameWidth+ plusSize, _imageInfo->frameHeight+ plusSize,
//			_imageInfo->hMemDC,
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,
//			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
//	}
//}

void image::frameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY)
{

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_isTrans)
	{
		//Gdi가 비트맵파일을 불러올때 특정 색상을 제외하고 복사해주는 함수.
		GdiTransparentBlt(
			hdc,												//복사될 장소의 DC
			destX,												//복사될 좌표의 시작점x
			destY,												//복사될 좌표의 시작점y
			_imageInfo->frameWidth,								//복사될 이미지의 가로크기
			_imageInfo->frameHeight,							//복사될 이미지의 세로크기
			_imageInfo->hMemDC,									//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	//복사 시작 지점의 x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//복사 시작 지점의 y
			_imageInfo->frameWidth,								//복사영역 가로 크기
			_imageInfo->frameHeight,							//복사영역 세로 크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속 복사.
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//보정하기
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);


	//그려지는(복사되어오는 이미지영역)
	RECT rcSour;
	
	int sourWidth;
	int sourHeight;

	//그려지는 DC영역
	RECT rcDest;
	
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;


	//세로 루프 영역
	for (size_t y = 0; y < drawAreaH; y+=sourHeight)
	{
		//영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//영역이 그리는 화면을 넘어갔다면(화면밖으로나갔을 때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀의 값을 올려줌
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (size_t x = 0; x < drawAreaW; x+=sourWidth)
		{
			//영역계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//화면 밖으로 넘어갔다면
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//그리자
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}

	}


}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//보정하기
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);


	//그려지는(복사되어오는 이미지영역)
	RECT rcSour;

	int sourWidth;
	int sourHeight;

	//그려지는 DC영역
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;


	//세로 루프 영역
	for (size_t y = 0; y < drawAreaH; y += sourHeight)
	{
		//영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//영역이 그리는 화면을 넘어갔다면(화면밖으로나갔을 때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀의 값을 올려줌
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (size_t x = 0; x < drawAreaW; x += sourWidth)
		{
			//영역계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//화면 밖으로 넘어갔다면
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그리자
			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, alpha);


		}

	}

}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;
	
	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else {
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, const int destX, const int destY, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else {
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else {
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY, BYTE alpha)
{
	if (!_blendImage) this->initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else {
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::aniRender(HDC hdc, const int destX, const int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::aniAlphaRender(HDC hdc, const int destX, const int destY, animation* ani, BYTE alpha)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

void image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	if (!_rotateImage) this->initForRotate();
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 - sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		SelectObject(_rotateImage->hMemDC, oBrush);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height,
			hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, SRCCOPY);
		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
		BitBlt(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2,
			_rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::rotateFrameRender(HDC hdc, float centerX, float centerY, const int frameX, const int frameY, float angle)
{
	if (!_rotateImage) this->initForRotate();
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 - sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		SelectObject(_rotateImage->hMemDC, oBrush);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	} 
	else
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height,
			hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, SRCCOPY);
		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC, 
			_imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
		BitBlt(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2,
			_rotateImage->width, _rotateImage->height, _rotateImage->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::rotateAlphaRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha)
{
	if (!_rotateImage) this->initForRotate();
	if (!_blendImage) this->initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 - sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		//로테dc에 검정칠하고 마젠타로바꾸고 -> 로테dc에 이미지 회전체올리고 -> 잠시대기
		//블랜dc에 원본깔고 -> 아까로테dc를 transcolor반영해서 블랜dc에 그리고 -> 얘를 원하는 dc에 옮길때 알파반영.
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height,
			hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, SRCCOPY);

		HBRUSH brush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, brush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		SelectObject(_rotateImage->hMemDC, oBrush);
		DeleteObject(brush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		AlphaBlend(hdc, centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width, _rotateImage->height,
			_blendImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);
	}
	else
	{	
		//로테dc에 원본배경깔고 -> 그위에 회전체 그리고 -> 로테dc를 원하는 dc에 옮길때 알파를 반영.
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height,
			hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, SRCCOPY);
		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
		AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height,
			_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);
	}
}

void image::rotateAlphaFrameRender(HDC hdc, float centerX, float centerY, int frameX, int frameY, float angle, BYTE alpha)
{
	if (!_rotateImage) this->initForRotate();
	if (!_blendImage) this->initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 - sinf(baseAngle[i] + angle) * dist);
	}


	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, SRCCOPY);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		GdiAlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_blendFunc);
	}
	else
	{
		//로테dc에 원본배경깔고 -> 그위에 회전체 그리고 -> 로테dc를 원하는 dc에 옮길때 알파를 반영.
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height,
			hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, SRCCOPY);
		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
		AlphaBlend(hdc, centerX - _rotateImage->width / 2, centerY - _rotateImage->height / 2, _rotateImage->width, _rotateImage->height,
			_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, _blendFunc);
	}
}

void image::rotateStretchRender(HDC hdc, float centerX, float centerY, float angle, float ratio)
{
	if (!_rotateImage) this->initForRotate();

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (!_stretchImage) this->initForStretch();
	_stretchImage->width = _rotateImage->width * ratio;
	_stretchImage->height = _rotateImage->height * ratio;

	if (true)
	{
		//읽기전에 알아둘것 : 로테이션dc를 커봣자 프레임의 대각선size고, 스트레치dc는 무궁무진하게 크다.
		//로테이션 dc를 블랙으로 칠하고, 전부 transcolor로 바꾸기
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		//스트레치 dc 스트레치모드 적용.
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		
		//회전해서 로테이션 dc에 그려두기 -> 로테이션 dc에는 대각선크기의 마젠타영역과 회전된 이미지가 오게됨.
		PlgBlt(_rotateImage->hMemDC, rPoint,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, NULL, 0, 0);
		
		//스트레치 dc에 로테이션 dc 확대/축소해서 가져오기.
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, SRCCOPY);

		//스트레치 dc에서 transcolor 제외하고 원하는 dc로 가져오기
		GdiTransparentBlt(hdc,
			centerX - _stretchImage->width / 2,
			centerY - _stretchImage->height / 2,
			_stretchImage->width,
			_stretchImage->height,
			_stretchImage->hMemDC,
			0, 0,
			_stretchImage->width,
			_stretchImage->height,
			_transColor);
	}
}

void image::rotateStretchFrameRender(HDC hdc, float centerX, float centerY, int frameX, int frameY, float angle, float ratio)
{
	if (!_rotateImage) this->initForRotate();

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (!_stretchImage) this->initForStretch();
	_stretchImage->width = _rotateImage->width * ratio;
	_stretchImage->height = _rotateImage->height * ratio;

	//transColor가 있던 없던 동일한 방법으로 출력한다.
	//보통 isTrans=false인 경우에는 마젠타투과할 필요가없엇지만,
	//회전시키는 로테이션 dc 자체가 이미지보다 반드시 크기 때문에
	//검정색이 배경에깔려잇거나, 지난번 작업내역이 남아있다.
	//때문에 그 영역에 isTrans=true일때와 같은방법으로 처리해서 출력해야한다.
	// 
	//그냥 로테이션 함수에서는  원본의 배경위에 isTrans=false인 이미지를 띄우면 자연스럽게
	//잔여 배경을 지울 수 있었으나,
	//여기서는 스트레치까지 진행해야하기 때문에, 원본 배경까지 스트레치되면 부자연스러으므로,
	//이 방법을 선택했다.
	if (true)
	{
		//읽기전에 알아둘것 : 로테이션dc를 커봣자 프레임의 대각선size고, 스트레치dc는 무궁무진하게 크다.
		//로테이션 dc를 블랙으로 칠하고, 전부 transcolor로 바꾸기
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		//스트레치 dc 스트레치모드 적용.
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);

		//회전해서 로테이션 dc에 그려두기 -> 로테이션 dc에는 대각선크기의 마젠타영역과 회전된 이미지가 오게됨.
		PlgBlt(_rotateImage->hMemDC, rPoint,
			_imageInfo->hMemDC, _imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);

		//스트레치 dc에 로테이션 dc 확대/축소해서 가져오기.
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, SRCCOPY);

		//스트레치 dc에서 transcolor 제외하고 원하는 dc로 가져오기
		GdiTransparentBlt(hdc,
			centerX - _stretchImage->width / 2,
			centerY - _stretchImage->height / 2,
			_stretchImage->width,
			_stretchImage->height,
			_stretchImage->hMemDC,
			0, 0,
			_stretchImage->width,
			_stretchImage->height,
			_transColor);
	}
}

void image::stretchRenderXY(HDC hdc, int destX, int destY, float ratio)
{
	if (!_stretchImage) this->initForStretch();
	_stretchImage->width = _imageInfo->width * ratio;
	_stretchImage->height = _imageInfo->height * ratio;

	if (_isTrans)
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			_stretchImage->width,	//복사될 이미지 가로크기
			_stretchImage->height,	//복사될 이미지 세로크기
			_stretchImage->hMemDC,	//복사될 대상 DC
			0, 0,					//복사 시작지점
			_stretchImage->width,	//복사 영역 가로크기
			_stretchImage->height,	//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else {
		//원본 이미지의 크기를 확대/축소 해서 렌더 시킨다
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, destX, destY, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::stretchRender(HDC hdc, int centerX, int centerY, float ratio)
{
	if (!_stretchImage) this->initForStretch();
	_stretchImage->width = _imageInfo->width * ratio;
	_stretchImage->height = _imageInfo->height * ratio;

	if (_isTrans)
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			centerX - _stretchImage->width / 2,					//복사될 좌표 시작점 X
			centerY - _stretchImage->height / 2,					//복사될 좌표 시작점 Y
			_stretchImage->width,	//복사될 이미지 가로크기
			_stretchImage->height,	//복사될 이미지 세로크기
			_stretchImage->hMemDC,	//복사될 대상 DC
			0, 0,					//복사 시작지점
			_stretchImage->width,	//복사 영역 가로크기
			_stretchImage->height,	//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else {
		//원본 이미지의 크기를 확대/축소 해서 렌더 시킨다
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, centerX - _stretchImage->width / 2, centerY - _stretchImage->height / 2, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::stretchRender(HDC hdc, int centerX, int centerY, int newWidth, int newHeight)
{
	if (!_stretchImage) this->initForStretch();
	_stretchImage->width = newWidth;
	_stretchImage->height = newHeight;

	if (_isTrans)
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			centerX - _stretchImage->width / 2,					//복사될 좌표 시작점 X
			centerY - _stretchImage->height / 2,					//복사될 좌표 시작점 Y
			_stretchImage->width,	//복사될 이미지 가로크기
			_stretchImage->height,	//복사될 이미지 세로크기
			_stretchImage->hMemDC,	//복사될 대상 DC
			0, 0,					//복사 시작지점
			_stretchImage->width,	//복사 영역 가로크기
			_stretchImage->height,	//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else {
		//원본 이미지의 크기를 확대/축소 해서 렌더 시킨다
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, centerX - _stretchImage->width / 2, centerY - _stretchImage->height / 2, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, float ratio)
{
	if (!_stretchImage) this->initForStretch();
	_stretchImage->width = _imageInfo->width * ratio;
	_stretchImage->height = _imageInfo->height * ratio;
	_stretchImage->frameWidth = _stretchImage->width / (_imageInfo->maxFrameX + 1);
	_stretchImage->frameHeight = _stretchImage->height / (_imageInfo->maxFrameY + 1);

	if (_isTrans)
	{
		//스트레치 dc에 프레임이미지를 잘라서 축소/확대시키고, 그것에서 transcolor를 빼고 원하는dc로 출력.
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);

		GdiTransparentBlt(
			hdc,							
			centerX - _stretchImage->frameWidth / 2,
			centerY - _stretchImage->frameHeight / 2,
			_stretchImage->frameWidth,	
			_stretchImage->frameHeight,		
			_stretchImage->hMemDC,			
			0, 0,							
			_stretchImage->frameWidth,		
			_stretchImage->frameHeight,		
			_transColor);					
	}
	else {
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, centerX - _stretchImage->frameWidth / 2, centerY - _stretchImage->frameHeight / 2, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, int newWidth, int newHeight)
{
	if (!_stretchImage) this->initForStretch();
	_stretchImage->frameWidth = newWidth;
	_stretchImage->frameHeight = newHeight;
	_stretchImage->width = newWidth * (_imageInfo->maxFrameX + 1);
	_stretchImage->height = newHeight * (_imageInfo->maxFrameY + 1);

	if (_isTrans)
	{
		//스트레치 dc에 프레임이미지를 잘라서 축소/확대시키고, 그것에서 transcolor를 빼고 원하는dc로 출력.
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);

		GdiTransparentBlt(
			hdc,
			centerX - _stretchImage->frameWidth / 2,
			centerY - _stretchImage->frameHeight / 2,
			_stretchImage->frameWidth,
			_stretchImage->frameHeight,
			_stretchImage->hMemDC,
			0, 0,
			_stretchImage->frameWidth,
			_stretchImage->frameHeight,
			_transColor);
	}
	else {
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, centerX - _stretchImage->frameWidth / 2, centerY - _stretchImage->frameHeight / 2, _stretchImage->frameWidth, _stretchImage->frameHeight,
			_imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, SRCCOPY);
	}
}

////테스트용 bitblt
//BitBlt(hdc, 100, 100,
//	_rotateImage->width, _rotateImage->height,
//	_blendImage->hMemDC, 0, 0, SRCCOPY);