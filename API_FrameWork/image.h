#pragma once
#include "animation.h"
class image
{
public:

	enum class IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ� �ε�
		LOAD_FILE,			//���Ϸε�
		LOAD_EMPTY,			//�� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD resID;			// ���ҽ�ID
		HDC hMemDC;				//�޸�DC
		HBITMAP hBit;			//��Ʈ��(���ο� ��Ʈ�� �ڵ�)
		HBITMAP hOBit;			//�õ��Ʈ��;
		int width;				//�̹��� ����ũ��
		int height;				//�̹��� ����ũ��
		BYTE loadType;			//� Ÿ������
		float x;				//�̹��� x��ǥ
		float y;				//�̹��� y��ǥ
		int currentFrameX;		//���������� X
		int currentFrameY;		//���������� Y
		int maxFrameX;			//�ִ� X������ ����
		int maxFrameY;			//�ִ� X������ ����
		int frameWidth;			//1������ ���α���
		int frameHeight;		//1������ ���α���


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
	LPIMAGE_INFO	_imageInfo;			//�̹��� ����
	char*			_fileName;			//�̹��� �̸�
	bool			_isTrans;			//���� ��������?
	COLORREF		_transColor;		//������ ���� RGB


	//���Ŀ�
	BLENDFUNCTION	_blendFunc;			//���ĺ��带 ����ϱ����� ����
	LPIMAGE_INFO	_blendImage;		//���ĺ��带 ����ϱ����� �̹��� ����
	
	//ȸ����
	LPIMAGE_INFO	_rotateImage;		//ȸ���̹���

	//��Ʈ��ġ��
	LPIMAGE_INFO	_stretchImage;		//��Ʈ��ġ �̹���

public:
	//��Ʈ�� �ʱ�ȭ
	HRESULT init(const int width, const int height);
	HRESULT init(const int width, const int height, COLORREF color);
	HRESULT init(const char * fileName, const int width, const int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char * fileName, const float x, const float y, const int width, const int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	
	//�����������ʱ�ȭ
	HRESULT init(const char* fileName, const int width, const int height, const int frameX, const int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	
	//Ư���ʱ�ȭ(hdc �߰� ����)
	HRESULT initForRotate();
	HRESULT initForAlphaBlend();
	HRESULT initForStretch();
	HRESULT initForStretch(int x, int y);
	
	//���� ����
	void setTransColor(bool isTrans, COLORREF transColor);
	
	void release();

	//����
	void render(HDC hdc);
	void render(HDC hdc, const int destX, const int destY);
	void render(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourheight);

	//������ ����
	void frameRender(HDC hdc);
	void frameRender(HDC hdc, const int destX, const int destY);
	void frameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);

	//���� ����
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, const int destX, const int destY, BYTE alpha);
	void alphaRender(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight, BYTE alpha);
	void alphaFrameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY, BYTE alpha);

	//�ִϸ��̼��ν��Ͻ� ����
	void aniRender(HDC hdc, const int destX, const int destY, animation* ani);
	void aniAlphaRender(HDC hdc, const int destX, const int destY, animation* ani, BYTE alpha);

	//ȸ�� ����
	void rotateRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, const int frameX, const int frameY, float angle);
	void rotateAlphaRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha);
	void rotateAlphaFrameRender(HDC hdc, float centerX, float centerY, int frameX, int frameY, float angle, BYTE alpha);
	void rotateStretchRender(HDC hdc, float centerX, float centerY, float angle, float ratio);
	void rotateStretchFrameRender(HDC hdc, float centerX, float centerY, int frameX, int frameY, float angle, float ratio);


	//��Ʈ��ġ ����
	void stretchRenderXY(HDC hdc, int destX, int destY, float ratio);
	void stretchRender(HDC hdc, int centerX, int centerY, float ratio);
	void stretchRender(HDC hdc, int centerX, int centerY, int newWidth, int newHeight);
	void stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, float ratio);
	void stretchFrameRender(HDC hdc, int centerX, int centerY, int currentFrameX, int currentFrameY, int newWidth, int newHeight);



	//DC�� �����Ͷ�
	inline HDC getMemDC()const { return _imageInfo->hMemDC; }


	//�̹��� ������ ���� �ϱ� ���� �Լ�
	//�̹��� x��ǥ
	inline float getX()const { return _imageInfo->x; }
	inline float setX(const float x) { return _imageInfo->x = x; }
	//�̹��� y��ǥ
	inline float getY()const { return _imageInfo->y; }
	inline float setY(const float y) { return _imageInfo->y = y; }

	inline void setCenter(const float x, const float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//���μ��� ũ�� ���
	inline int getWidth()const { return _imageInfo->width; }
	inline int getHeight()const { return _imageInfo->height; }
	inline void setWidth(int width)const { _imageInfo->width = width; }
	inline void setHeight(int height)const { _imageInfo->height = height; }
	

	//�ٿ�� �ڽ�(�浹��)
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


	//������ x ����
	inline int getFrameX()const { return _imageInfo->currentFrameX; }
	inline void setFrameX(const int frameX) 
	{ 
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//������ y ����
	inline int getFrameY()const { return _imageInfo->currentFrameY; }
	inline void setFrameY(const int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	//1������ ���μ��� ũ�� ���
	inline int getFrameWidth()const { return _imageInfo->frameWidth; }
	inline int getFrameHeight()const { return _imageInfo->frameHeight; }

	//�ƽ������� ���μ��� ũ�� ���
	inline int getMaxFrameX()const { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY()const { return _imageInfo->maxFrameY; }



};

