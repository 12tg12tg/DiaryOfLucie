#include "framework.h"
#include "effectTest.h"

effectTest::effectTest()
{
}

effectTest::~effectTest()
{
}

HRESULT effectTest::init()
{
	IMAGE->addImage("¹è°æ", "images/»ç³ª.bmp", WINSIZEX, WINSIZEY);
	
	////Æø¹ßÀÌÆåÆ® Ãß°¡
	//IMAGE->addImage("Æø¹ß", "images/explosion.bmp", 832, 62, true);
	//IMAGE->addImage("Æø¹ß1", "images/explosion1.bmp", 4355, 135, true);

	//_effect = new effect;
	//_effect->init(IMAGE->findImage("Æø¹ß"), 32, 62, 1, 0.5f);

	//_effect1 = new effect;
	//_effect1->init(IMAGE->findImage("Æø¹ß1"), 335, 135, 1, 0.4f);

	//¸Å´ÏÀú»ç¿ë
	count = 0;
	EFFECT->addEffect("Æø¹ß", "images/explosion.bmp", 832, 62, 32, 62, 1, 0.5f, 1);
	EFFECT->addEffect("Æø¹ß1", "images/explosion1.bmp", 4335, 135, 335, 135, 1, 0.3f, 1);


	return S_OK;
}

void effectTest::release()
{
	//SAFE_DELETE(_effect);
	//SAFE_DELETE(_effect1);
}

void effectTest::update()
{
	if (InputManager->isOnceKeyDown(VK_LBUTTON))
	{
		//_effect->startEffect(m_ptMouse.x, m_ptMouse.y);
		EFFECT->play("Æø¹ß", m_ptMouse.x, m_ptMouse.y);
	}
	if (InputManager->isOnceKeyDown(VK_RBUTTON))
	{
		//_effect1->startEffect(m_ptMouse.x, m_ptMouse.y);
		EFFECT->play("Æø¹ß1", m_ptMouse.x, m_ptMouse.y);
	}

	count++;
	if (count % 10 == 0)
	{
		EFFECT->play("Æø¹ß", RND->getFromInTo(100, 300), RND->getFromInTo(100, 300));
	}

	//_effect->update();
	//_effect1->update();
}

void effectTest::render()
{
	//IMAGE->render("¹è°æ", getMemDC());
	//_effect->render();
	//_effect1->render();
}
