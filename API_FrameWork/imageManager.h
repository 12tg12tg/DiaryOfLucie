#pragma once
#include"singleton.h"
#include"image.h"
class imageManager : public Singleton<imageManager>
{
private:
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageListIter;

	mapImageList _mImageList;
public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	//Ű������ �� ��Ʈ�� �ʱ�ȭ
	image* addImage(string strkey, const int width, const int height);
	image* addImage(string strkey, const char* fileName, const int width, const int height, bool trans = false, COLORREF transColor=RGB(255, 0, 255));
	image* addImage(string strkey, const char* fileName, const float x, const float y, const int width, const int height, bool trans = false, COLORREF transColor = RGB(255, 0, 255));

	//Ű������ �̹��� ������ �ʱ�ȭ
	image* addFrameImage(string strkey, const char* fileName, const int width, const int height, const int frameX, const int frameY, bool trans = false, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strkey, const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool trans = false, COLORREF transColor = RGB(255, 0, 255));

	//�̹����� ã�ƶ�
	image* findImage(string strkey);
	//�̹��� Ű������ ����
	bool deleteImage(string strkey);
	//�̹��� ��ü ����
	bool deleteAll();

	//����
	void render(string strkey, HDC hdc);
	void render(string strkey, HDC hdc, const int destX, const int destY);
	void render(string strkey, HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight);

	//������
	void frameRender(string strkey, HDC hdc);
	void frameRender(string strkey, HDC hdc, const int destX, const int destY);
	void frameRender(string strkey, HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);
	void loopRender(string strkey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strkey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);
};

