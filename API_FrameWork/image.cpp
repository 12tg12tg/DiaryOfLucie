#include"framework.h"
#include "image.h"
//���ĺ��带 ����ϱ� ����
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
	//�̹��� ������ ��������� �����϶�.
	if (_imageInfo != NULL) release();

	//DC��������(���� �����쿡 ���� ȭ�� DC�� �ӽ÷� ������)
	HDC hdc = GetDC(m_hWnd);

	//CreateCompatibleDC : ��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ������ش�.
	//CreateCompatibleBitmap : ����DC�� ȣȯ�Ǵ� ��Ʈ�� ����.
	
	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //��Ʈ����������ظ޸�dc�� ������ִ� �Լ�.
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //����dc�� ȣȯ�Ǵ� ��Ʈ���� ����.
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸� �ʱ�ȭ
	_fileName = NULL;


	//����Ű ����
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//���ҽ��� �����µ� �����ϸ�
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
	//�̹��� ������ ��������� �����϶�.
	if (_imageInfo != NULL) release();

	//DC��������(���� �����쿡 ���� ȭ�� DC�� �ӽ÷� ������)
	HDC hdc = GetDC(m_hWnd);

	//CreateCompatibleDC : ��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ������ش�.
	//CreateCompatibleBitmap : ����DC�� ȣȯ�Ǵ� ��Ʈ�� ����.

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //��Ʈ����������ظ޸�dc�� ������ִ� �Լ�.
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //����dc�� ȣȯ�Ǵ� ��Ʈ���� ����.
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸� �ʱ�ȭ
	_fileName = NULL;

	//����Ű ����
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//���ҽ��� �����µ� �����ϸ�
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


	//�����̸�
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ϸ�
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
	//�̰Ծ��������־���?
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


	//�����̸�
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ϸ�
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


	//�����̸�
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ϸ�
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


	//�����̸�
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ��� �����µ� �����ϸ�
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

		//���� ���� �ɼ�
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER; //���� ������


		//���� ���� ����ϱ� ���� �̹��� �ʱ�ȭ
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

		//���� ���� �ɼ�
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER; //���� ������


		//���� ���� ����ϱ� ���� �̹��� �ʱ�ȭ
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
	//���ĺ��� �̹��� ������ �ִٸ� ����
	if (_blendImage)
	{
		//�̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//������ ����
		SAFE_DELETE(_blendImage);
	}
	//������Ʈ���� ����
	if (_rotateImage)
	{
		//�̹��� ����
		SelectObject(_rotateImage->hMemDC, _rotateImage->hOBit);
		DeleteObject(_rotateImage->hBit);
		DeleteDC(_rotateImage->hMemDC);

		//������ ����
		SAFE_DELETE(_rotateImage);
	}
	if (_stretchImage)
	{
		//�̹��� ����
		SelectObject(_stretchImage->hMemDC, _stretchImage->hOBit);
		DeleteObject(_stretchImage->hBit);
		DeleteDC(_stretchImage->hMemDC);

		//������ ����
		SAFE_DELETE(_stretchImage);
	}
}

void image::render(HDC hdc)
{
	if (_isTrans)
	{
		//Gdi�� ��Ʈ�������� �ҷ��ö� Ư�� ������ �����ϰ� �������ִ� �Լ�.
		GdiTransparentBlt(
			hdc,						//����� ����� DC
			_imageInfo->x,							//����� ��ǥ�� ������x
			_imageInfo->y,							//����� ��ǥ�� ������y
			_imageInfo->width,			//����� �̹����� ����ũ��
			_imageInfo->height,			//����� �̹����� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			0,							//���� ���� ������ x
			0,							//���� ���� ������ y
			_imageInfo->width,			//���翵�� ���� ũ��
			_imageInfo->height,			//���翵�� ���� ũ��
			_transColor);
	}
	else {
		//BitBlt : DC�������� ��� ����.
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY); 
	}
}

void image::render(HDC hdc, const int destX, const int destY)
{
	if (_isTrans)
	{
		//Gdi�� ��Ʈ�������� �ҷ��ö� Ư�� ������ �����ϰ� �������ִ� �Լ�.
		GdiTransparentBlt(
			hdc,						//����� ����� DC
			destX,							//����� ��ǥ�� ������x
			destY,							//����� ��ǥ�� ������y
			_imageInfo->width,			//����� �̹����� ����ũ��
			_imageInfo->height,			//����� �̹����� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			0,							//���� ���� ������ x
			0,							//���� ���� ������ y
			_imageInfo->width,			//���翵�� ���� ũ��
			_imageInfo->height,			//���翵�� ���� ũ��
			_transColor);
	}
	else {
		//BitBlt : DC�������� ��� ����.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
//void image::�ڡڡ�(HDC hdc, const int destX, const int destY, int plusSize)
//{
//	if (_isTrans)
//	{
//		//Gdi�� ��Ʈ�������� �ҷ��ö� Ư�� ������ �����ϰ� �������ִ� �Լ�.
//		GdiTransparentBlt(
//			hdc,						//����� ����� DC
//			destX,							//����� ��ǥ�� ������x
//			destY,							//����� ��ǥ�� ������y
//			_imageInfo->width + plusSize,			//����� �̹����� ����ũ��
//			_imageInfo->height + plusSize,			//����� �̹����� ����ũ��
//			_imageInfo->hMemDC,			//����� ��� DC
//			0,							//���� ���� ������ x
//			0,							//���� ���� ������ y
//			_imageInfo->width,			//���翵�� ���� ũ��
//			_imageInfo->height,			//���翵�� ���� ũ��
//			_transColor);
//	}
//	else {
//		//BitBlt : DC�������� ��� ����.
//		BitBlt(hdc, destX, destY, _imageInfo->width + plusSize, _imageInfo->height + plusSize,
//			_imageInfo->hMemDC, 0, 0, SRCCOPY);
//	}
//}
void image::render(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourheight)
{
	if (_isTrans)
	{
		//Gdi�� ��Ʈ�������� �ҷ��ö� Ư�� ������ �����ϰ� �������ִ� �Լ�.
		GdiTransparentBlt(
			hdc,						//����� ����� DC
			destX,							//����� ��ǥ�� ������x
			destY,							//����� ��ǥ�� ������y
			sourWidth,			//����� �̹����� ����ũ��
			sourheight,			//����� �̹����� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			sourX,							//���� ���� ������ x
			sourY,							//���� ���� ������ y
			sourWidth,			//���翵�� ���� ũ��
			sourheight,			//���翵�� ���� ũ��
			_transColor);
	}
	else {
		//BitBlt : DC�������� ��� ����.
		BitBlt(hdc, destX, destY, sourWidth, sourheight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc)
{
	if (_isTrans)
	{
		//Gdi�� ��Ʈ�������� �ҷ��ö� Ư�� ������ �����ϰ� �������ִ� �Լ�.
		GdiTransparentBlt(
			hdc,												//����� ����� DC
			_imageInfo->x,												//����� ��ǥ�� ������x
			_imageInfo->y,												//����� ��ǥ�� ������y
			_imageInfo->frameWidth,								//����� �̹����� ����ũ��
			_imageInfo->frameHeight,							//����� �̹����� ����ũ��
			_imageInfo->hMemDC,									//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	//���� ���� ������ x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� ���� ������ y
			_imageInfo->frameWidth,								//���翵�� ���� ũ��
			_imageInfo->frameHeight,							//���翵�� ���� ũ��
			_transColor);
	}
	else {
		//BitBlt : DC�������� ��� ����.
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
		//Gdi�� ��Ʈ�������� �ҷ��ö� Ư�� ������ �����ϰ� �������ִ� �Լ�.
		GdiTransparentBlt(
			hdc,												//����� ����� DC
			destX,												//����� ��ǥ�� ������x
			destY,												//����� ��ǥ�� ������y
			_imageInfo->frameWidth,								//����� �̹����� ����ũ��
			_imageInfo->frameHeight,							//����� �̹����� ����ũ��
			_imageInfo->hMemDC,									//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	//���� ���� ������ x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� ���� ������ y
			_imageInfo->frameWidth,								//���翵�� ���� ũ��
			_imageInfo->frameHeight,							//���翵�� ���� ũ��
			_transColor);
	}
	else {
		//BitBlt : DC�������� ��� ����.
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

//void image::�١١�(HDC hdc, const int destX, const int destY, int plusSize)
//{
//	if (_isTrans)
//	{
//		//Gdi�� ��Ʈ�������� �ҷ��ö� Ư�� ������ �����ϰ� �������ִ� �Լ�.
//		GdiTransparentBlt(
//			hdc,												//����� ����� DC
//			destX,												//����� ��ǥ�� ������x
//			destY,												//����� ��ǥ�� ������y
//			_imageInfo->frameWidth + plusSize,					//����� �̹����� ����ũ��
//			_imageInfo->frameHeight + plusSize,					//����� �̹����� ����ũ��
//			_imageInfo->hMemDC,									//����� ��� DC
//			_imageInfo->currentFrameX * _imageInfo->frameWidth,	//���� ���� ������ x
//			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� ���� ������ y
//			_imageInfo->frameWidth,								//���翵�� ���� ũ��
//			_imageInfo->frameHeight,							//���翵�� ���� ũ��
//			_transColor);
//	}
//	else {
//		//BitBlt : DC�������� ��� ����.
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
		//Gdi�� ��Ʈ�������� �ҷ��ö� Ư�� ������ �����ϰ� �������ִ� �Լ�.
		GdiTransparentBlt(
			hdc,												//����� ����� DC
			destX,												//����� ��ǥ�� ������x
			destY,												//����� ��ǥ�� ������y
			_imageInfo->frameWidth,								//����� �̹����� ����ũ��
			_imageInfo->frameHeight,							//����� �̹����� ����ũ��
			_imageInfo->hMemDC,									//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,	//���� ���� ������ x
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//���� ���� ������ y
			_imageInfo->frameWidth,								//���翵�� ���� ũ��
			_imageInfo->frameHeight,							//���翵�� ���� ũ��
			_transColor);
	}
	else {
		//BitBlt : DC�������� ��� ����.
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�����ϱ�
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);


	//�׷�����(����Ǿ���� �̹�������)
	RECT rcSour;
	
	int sourWidth;
	int sourHeight;

	//�׷����� DC����
	RECT rcDest;
	
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;


	//���� ���� ����
	for (size_t y = 0; y < drawAreaH; y+=sourHeight)
	{
		//������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������γ����� ��)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ������ ���� �÷���
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (size_t x = 0; x < drawAreaW; x+=sourWidth)
		{
			//�������
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//ȭ�� ������ �Ѿ�ٸ�
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//�׸���
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}

	}


}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//�����ϱ�
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);


	//�׷�����(����Ǿ���� �̹�������)
	RECT rcSour;

	int sourWidth;
	int sourHeight;

	//�׷����� DC����
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;


	//���� ���� ����
	for (size_t y = 0; y < drawAreaH; y += sourHeight)
	{
		//������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������γ����� ��)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ������ ���� �÷���
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (size_t x = 0; x < drawAreaW; x += sourWidth)
		{
			//�������
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//ȭ�� ������ �Ѿ�ٸ�
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׸���
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

	//���İ� �ʱ�ȭ
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

	//���İ� �ʱ�ȭ
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

	//���İ� �ʱ�ȭ
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

	//���İ� �ʱ�ȭ
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
		//����dc�� ����ĥ�ϰ� ����Ÿ�ιٲٰ� -> ����dc�� �̹��� ȸ��ü�ø��� -> ��ô��
		//��dc�� ������� -> �Ʊ����dc�� transcolor�ݿ��ؼ� ��dc�� �׸��� -> �긦 ���ϴ� dc�� �ű涧 ���Ĺݿ�.
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
		//����dc�� ��������� -> ������ ȸ��ü �׸��� -> ����dc�� ���ϴ� dc�� �ű涧 ���ĸ� �ݿ�.
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
		//����dc�� ��������� -> ������ ȸ��ü �׸��� -> ����dc�� ���ϴ� dc�� �ű涧 ���ĸ� �ݿ�.
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
		//�б����� �˾ƵѰ� : �����̼�dc�� Ŀ�f�� �������� �밢��size��, ��Ʈ��ġdc�� ���ù����ϰ� ũ��.
		//�����̼� dc�� ������ ĥ�ϰ�, ���� transcolor�� �ٲٱ�
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		//��Ʈ��ġ dc ��Ʈ��ġ��� ����.
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		
		//ȸ���ؼ� �����̼� dc�� �׷��α� -> �����̼� dc���� �밢��ũ���� ����Ÿ������ ȸ���� �̹����� ���Ե�.
		PlgBlt(_rotateImage->hMemDC, rPoint,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, NULL, 0, 0);
		
		//��Ʈ��ġ dc�� �����̼� dc Ȯ��/����ؼ� ��������.
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, SRCCOPY);

		//��Ʈ��ġ dc���� transcolor �����ϰ� ���ϴ� dc�� ��������
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

	//transColor�� �ִ� ���� ������ ������� ����Ѵ�.
	//���� isTrans=false�� ��쿡�� ����Ÿ������ �ʿ䰡��������,
	//ȸ����Ű�� �����̼� dc ��ü�� �̹������� �ݵ�� ũ�� ������
	//�������� ��濡����հų�, ������ �۾������� �����ִ�.
	//������ �� ������ isTrans=true�϶��� ����������� ó���ؼ� ����ؾ��Ѵ�.
	// 
	//�׳� �����̼� �Լ�������  ������ ������� isTrans=false�� �̹����� ���� �ڿ�������
	//�ܿ� ����� ���� �� �־�����,
	//���⼭�� ��Ʈ��ġ���� �����ؾ��ϱ� ������, ���� ������ ��Ʈ��ġ�Ǹ� ���ڿ��������Ƿ�,
	//�� ����� �����ߴ�.
	if (true)
	{
		//�б����� �˾ƵѰ� : �����̼�dc�� Ŀ�f�� �������� �밢��size��, ��Ʈ��ġdc�� ���ù����ϰ� ũ��.
		//�����̼� dc�� ������ ĥ�ϰ�, ���� transcolor�� �ٲٱ�
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		//��Ʈ��ġ dc ��Ʈ��ġ��� ����.
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);

		//ȸ���ؼ� �����̼� dc�� �׷��α� -> �����̼� dc���� �밢��ũ���� ����Ÿ������ ȸ���� �̹����� ���Ե�.
		PlgBlt(_rotateImage->hMemDC, rPoint,
			_imageInfo->hMemDC, _imageInfo->frameWidth * frameX, _imageInfo->frameHeight * frameY,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);

		//��Ʈ��ġ dc�� �����̼� dc Ȯ��/����ؼ� ��������.
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, SRCCOPY);

		//��Ʈ��ġ dc���� transcolor �����ϰ� ���ϴ� dc�� ��������
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
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ X
			destY,					//����� ��ǥ ������ Y
			_stretchImage->width,	//����� �̹��� ����ũ��
			_stretchImage->height,	//����� �̹��� ����ũ��
			_stretchImage->hMemDC,	//����� ��� DC
			0, 0,					//���� ��������
			_stretchImage->width,	//���� ���� ����ũ��
			_stretchImage->height,	//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)
	}
	else {
		//���� �̹����� ũ�⸦ Ȯ��/��� �ؼ� ���� ��Ų��
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
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			centerX - _stretchImage->width / 2,					//����� ��ǥ ������ X
			centerY - _stretchImage->height / 2,					//����� ��ǥ ������ Y
			_stretchImage->width,	//����� �̹��� ����ũ��
			_stretchImage->height,	//����� �̹��� ����ũ��
			_stretchImage->hMemDC,	//����� ��� DC
			0, 0,					//���� ��������
			_stretchImage->width,	//���� ���� ����ũ��
			_stretchImage->height,	//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)
	}
	else {
		//���� �̹����� ũ�⸦ Ȯ��/��� �ؼ� ���� ��Ų��
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
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			centerX - _stretchImage->width / 2,					//����� ��ǥ ������ X
			centerY - _stretchImage->height / 2,					//����� ��ǥ ������ Y
			_stretchImage->width,	//����� �̹��� ����ũ��
			_stretchImage->height,	//����� �̹��� ����ũ��
			_stretchImage->hMemDC,	//����� ��� DC
			0, 0,					//���� ��������
			_stretchImage->width,	//���� ���� ����ũ��
			_stretchImage->height,	//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)
	}
	else {
		//���� �̹����� ũ�⸦ Ȯ��/��� �ؼ� ���� ��Ų��
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
		//��Ʈ��ġ dc�� �������̹����� �߶� ���/Ȯ���Ű��, �װͿ��� transcolor�� ���� ���ϴ�dc�� ���.
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
		//��Ʈ��ġ dc�� �������̹����� �߶� ���/Ȯ���Ű��, �װͿ��� transcolor�� ���� ���ϴ�dc�� ���.
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

////�׽�Ʈ�� bitblt
//BitBlt(hdc, 100, 100,
//	_rotateImage->width, _rotateImage->height,
//	_blendImage->hMemDC, 0, 0, SRCCOPY);