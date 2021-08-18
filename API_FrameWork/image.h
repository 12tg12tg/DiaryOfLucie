#pragma once
#include "animation.h"
class image
{
public:

	enum class IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스 로딩
		LOAD_FILE,			//파일로딩
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD resID;			// 리소스ID
		HDC hMemDC;				//메모리DC
		HBITMAP hBit;			//비트맵(새로운 비트맵 핸들)
		HBITMAP hOBit;			//올드비트맵;
		int width;				//이미지 가로크기
		int height;				//이미지 세로크기
		BYTE loadType;			//어떤 타입인지
		float x;				//이미지 x좌표
		float y;				//이미지 y좌표
		int currentFrameX;		//현재프레임 X
		int currentFrameY;		//현재프레임 Y
		int maxFrameX;			//최대 X프레임 갯수
		int maxFrameY;			//최대 X프레임 갯수
		int frameWidth;			//1프레임 가로길이
		int frameHeight;		//1프레임 세로길이


		tagImage()
		{
			resID = 0;
			hMemDC = NULL,
			hBit = NULL,
			hOBit = NULL,
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_RESOURCE);
		}
	}IMAGE_INFO, *LPIMAGE_INFO;


	image();
	~image();

private:
	LPIMAGE_INFO	_imageInfo;			//이미지 정보
	char*			_fileName;			//이미지 이름
	bool			_isTrans;			//배경색 날릴꺼냐?
	COLORREF		_transColor;		//배경색을 날릴 RGB


	//알파용
	BLENDFUNCTION	_blendFunc;			//알파블렌드를 사용하기위한 정보
	LPIMAGE_INFO	_blendImage;		//알파블렌드를 사용하기위한 이미지 정보
	
	//회전용
	LPIMAGE_INFO	_rotateImage;		//회전이미지

	//스트레치용
	LPIMAGE_INFO	_stretchImage;		//스트레치 이미지

public:
	//비트맵 초기화
	HRESULT init(const int width, const int height);
	HRESULT init(const int width, const int height, COLORREF color);
	HRESULT init(const char * fileName, const int width, const int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char * fileName, const float x, const float y, const int width, const int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	
	//프레임이지초기화
	HRESULT init(const char* fileName, const int width, const int height, const int frameX, const int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	
	//특수초기화(hdc 추가 생성)
	HRESULT initForRotate();
	HRESULT initForAlphaBlend();
	HRESULT initForStretch();
	HRESULT initForStretch(int x, int y);
	
	//투명값 셋팅
	void setTransColor(bool isTrans, COLORREF transColor);
	
	void release();

	//렌더
	void render(HDC hdc);
	void render(HDC hdc, const int destX, const int destY);
	void render(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourheight);

	//프레임 렌더
	void frameRender(HDC hdc);
	void frameRender(HDC hdc, const int destX, const int destY);
	void frameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);

	//루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, const int destX, const int destY, BYTE alpha);
	void alphaRender(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight, BYTE alpha);
	void alphaFrameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY, BYTE alpha);

	//애니메이션인스턴스 렌더
	void aniRender(HDC hdc, const int destX, const int destY, animation* ani);
	void aniAlphaRender(HDC hdc, const int destX, const int destY, animation* ani, BYTE alpha);

	//회전 랜더
	void rotateRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, const int frameX, const int frameY, float angle);
	void rotateAlphaRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha);
	void rotateAlphaFrameRender(HDC hdc, float centerX, float centerY, int frameX, int frameY, float angle, BYTE alpha);
	void rotateStretchRender(HDC hdc, float centerX, float centerY, float angle, float ratio);
	void rotateStretchFrameRender(HDC hdc, float centerX, float centerY, int frameX, int frameY, float angle, float ratio);


	//스트레치 랜더
	void stretchRenderXY(HDC hdc, int destX, int destY, float ratio);
	void stretchRender(HDC hdc, int centerX, int centerY, float ratio);
	void stretchRender(HDC hdc, int centerX, int centerY, int newWidth, int newHeight);
	void stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, float ratio);
	void stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, int newWidth, int newHeight);



	//DC를 가져와라
	inline HDC getMemDC()const { return _imageInfo->hMemDC; }


	//이미지 조작을 쉽게 하기 위한 함수
	//이미지 x좌표
	inline float getX()const { return _imageInfo->x; }
	inline float setX(const float x) { return _imageInfo->x = x; }
	//이미지 y좌표
	inline float getY()const { return _imageInfo->y; }
	inline float setY(const float y) { return _imageInfo->y = y; }

	inline void setCenter(const float x, const float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//가로세로 크기 얻기
	inline int getWidth()const { return _imageInfo->width; }
	inline int getHeight()const { return _imageInfo->height; }
	inline void setWidth(int width)const { _imageInfo->width = width; }
	inline void setHeight(int height)const { _imageInfo->height = height; }
	

	//바운딩 박스(충돌용)
	inline RECT getBoundingBox()
	{
		RECT rc;
		if (_imageInfo->maxFrameX == 0 && _imageInfo->maxFrameY == 0)
			rc = RectMake(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
		else
			rc = RectMake(_imageInfo->x, _imageInfo->y,
				_imageInfo->width / (_imageInfo->maxFrameX + 1),
				_imageInfo->height / (_imageInfo->maxFrameY + 1));
		return rc;
	}
	inline RECT getBoundingBox(int x, int y)
	{
		RECT rc;
		if (_imageInfo->maxFrameX == 0 && _imageInfo->maxFrameY == 0)
			rc = RectMake(x, y, _imageInfo->width, _imageInfo->height);
		else
			rc = RectMake(x, y,
				_imageInfo->width / (_imageInfo->maxFrameX + 1),
				_imageInfo->height / (_imageInfo->maxFrameY + 1));
		return rc;
	}


	//프레임 x 셋팅
	inline int getFrameX()const { return _imageInfo->currentFrameX; }
	inline void setFrameX(const int frameX) 
	{ 
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//프레임 y 셋팅
	inline int getFrameY()const { return _imageInfo->currentFrameY; }
	inline void setFrameY(const int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	//1프레임 가로세로 크기 얻기
	inline int getFrameWidth()const { return _imageInfo->frameWidth; }
	inline int getFrameHeight()const { return _imageInfo->frameHeight; }

	//맥스프레임 가로세로 크기 얻기
	inline int getMaxFrameX()const { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY()const { return _imageInfo->maxFrameY; }



};

