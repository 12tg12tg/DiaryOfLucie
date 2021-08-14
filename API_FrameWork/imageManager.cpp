#include"framework.h"
#include "imageManager.h"

imageManager::imageManager()
{
}

imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}

image* imageManager::addImage(string strkey, const int width, const int height)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strkey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img) return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	_mImageList.insert(make_pair(strkey, img));
	return img;








}

image* imageManager::addImage(string strkey, const char* fileName, const int width, const int height, bool trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strkey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img) return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	_mImageList.insert(make_pair(strkey, img));
	return img;
}

image* imageManager::addImage(string strkey, const char* fileName, const float x, const float y, const int width, const int height, bool trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strkey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img) return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	_mImageList.insert(make_pair(strkey, img));
	return img;
}

image* imageManager::addFrameImage(string strkey, const char* fileName, const int width, const int height, const int frameX, const int frameY, bool trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strkey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img) return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	_mImageList.insert(make_pair(strkey, img));
	return img;
}

image* imageManager::addFrameImage(string strkey, const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool trans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹��� �����ϴ��� Ȯ��
	image* img = findImage(strkey);
	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img) return img;

	img = new image;

	//�̹����� �ʱ�ȭ���� ������
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	_mImageList.insert(make_pair(strkey, img));
	return img;
}

image* imageManager::findImage(string strkey)
{
	//�ش�Ű �˻�
	mapImageListIter key = _mImageList.find(strkey);
	//Ű�� ã����
	if (key != _mImageList.end())
	{
		return key->second;
	}
	return NULL;
}

bool imageManager::deleteImage(string strkey)
{
	//�ش�Ű �˻�
	mapImageListIter key = _mImageList.find(strkey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);
		return true;
	}
	return false;
}

bool imageManager::deleteAll()
{
	//��ü�� ���鼭 ����
	mapImageListIter iter = _mImageList.begin();

	for (iter; iter != _mImageList.end(); )
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}
	_mImageList.clear();
	return true;
}

void imageManager::render(string strkey, HDC hdc)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strkey);
	if (img) img->render(hdc);
}

void imageManager::render(string strkey, HDC hdc, const int destX, const int destY)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strkey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strkey, HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight)
{
	image* img = findImage(strkey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strkey, HDC hdc)
{
	image* img = findImage(strkey);
	if (img) img->frameRender(hdc);
}

void imageManager::frameRender(string strkey, HDC hdc, const int destX, const int destY)
{
	image* img = findImage(strkey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strkey, HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY)
{
	image* img = findImage(strkey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::loopRender(string strkey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	image* img = findImage(strkey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strkey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	image* img = findImage(strkey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}
