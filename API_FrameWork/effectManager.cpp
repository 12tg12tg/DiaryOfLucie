#include "framework.h"
#include "effectManager.h"
#include "effect.h"
effectManager::effectManager()
{
}

effectManager::~effectManager()
{
}

HRESULT effectManager::init()
{

    return S_OK;
}

void effectManager::release()
{
    viTotalEffect vIter;        //��� ����Ʈ ������ ����
    miEffect mIter;             //����ƮŬ������ ��� ���� ���� �ݺ���

    for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
    {
        //����Ʈ�� ��� �� vIter
        for (mIter = vIter->begin(); mIter != vIter->end(); )
        {
            //����� ������ �����.
            if (mIter->second.size() != 0)
            {
                //����Ʈ Ŭ������ ���� ����
                viEffect vArriter;
                for (vArriter = mIter->second.begin(); vArriter!=mIter->second.end(); )
                {
                    //����Ʈ Ŭ���� ������
                    (*vArriter)->release();
                    SAFE_DELETE(*vArriter);
                    vArriter = mIter->second.erase(vArriter);
                }
            }
            else 
            {
                ++mIter;
            }
        }
    }

}

void effectManager::update()
{
    viTotalEffect vIter;        //��� ����Ʈ ������ ����
    miEffect mIter;             //����ƮŬ������ ��� ���� ���� �ݺ���

    for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
    {
        for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
        {
            viEffect vArriter;
            for (vArriter = mIter->second.begin(); vArriter != mIter->second.end(); ++vArriter)
            {
                (*vArriter)->update();
            }

        }
    }

    //��ƼŬ
    for (int i = 0; i < _vParticle.size();)
    {
        //������������ �̵�.
        _vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
        _vParticle[i].y -= sinf(_vParticle[i].angle) * _vParticle[i].speed;
        _vParticle[i].count--;
        //�����ֱ⸶�� ���İ�, �ޱ� ����
        if (_vParticle[i].count % 5 == 0) {
            _vParticle[i].angle = _vParticle[i].angle + DEGREE(RND->getInt(10) - 5);
        }
        if (_vParticle[i].count % 12 == 0) {
            _vParticle[i].alpha = _vParticle[i].alpha - RND->getInt(6);
        }
        //���� ���ϸ� ����.
        if (_vParticle[i].count <= 0)
            _vParticle.erase(_vParticle.begin() + i);
        else
            i++;
    }
}

void effectManager::render()
{
    viTotalEffect vIter;        //��� ����Ʈ ������ ����
    miEffect mIter;             //����ƮŬ������ ��� ���� ���� �ݺ���

    for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
    {
        for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
        {
            viEffect vArriter;
            for (vArriter = mIter->second.begin(); vArriter != mIter->second.end(); ++vArriter)
            {
                (*vArriter)->render();
            }

        }
    }

    //��ƼŬ ����
    for (int i = 0; i < _vParticle.size(); i++)
    {
        if (_vParticle[i].isAlpha)
            ZORDER->ZorderAlphaRender(IMAGE->findImage(_vParticle[i].imgKey), _vParticle[i].z,
                _vParticle[i].y, _vParticle[i].x, _vParticle[i].y, _vParticle[i].alpha);
        else
            ZORDER->ZorderRender(IMAGE->findImage(_vParticle[i].imgKey), _vParticle[i].z, _vParticle[i].y,
                _vParticle[i].x, _vParticle[i].y);
    }

}

void effectManager::addEffect(string effectKey, char* imageName, float z, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer, BYTE alpha)
{
    image* img;
    vEffect vEffectBuffer;
    mEffect mArrEffect;

    if (IMAGE->findImage(imageName))
    {
        img = IMAGE->findImage(imageName);
    }
    else
    {
        img = IMAGE->addImage(effectKey, imageName, imageW, imageH, true, RGB(255, 0, 255));
    }

    //����ũ�⸸ŭ ����Ʈ�� �Ҵ� �� �ʱ�ȭ �ؼ� ���ͷ� �����.
    for (size_t i = 0; i < buffer; i++)
    {
        vEffectBuffer.push_back(new effect);
        vEffectBuffer[i]->init(img, z, frameW, frameH, fps, elapsedTime, alpha);
    }

    //���۸� �ʿ� �־��ְ�
    mArrEffect.insert(make_pair(effectKey, vEffectBuffer));
    //��Ż���ۿ� ���� �ִ´�.
    m_vTotalEffect.push_back(mArrEffect);
}

void effectManager::play(string effectKey, int x, int y)
{
    viTotalEffect vIter;
    miEffect mIter;

    for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
    {
        for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
        {
            //ã�� Ű���� �ƴ϶�� �� ���� �ٷ� ��������.
            if (!(mIter->first == effectKey)) break;

            //����Ʈ Ű���� ��ġ�ϸ� ����Ʈ�� �÷�������.
            viEffect vArriter;
            for (vArriter = mIter->second.begin(); vArriter != mIter->second.end(); ++vArriter)
            {
                if ((*vArriter)->getIsRunning()) continue;
                (*vArriter)->startEffect(x, y);
                return;
            }
        }
    }
}

HRESULT effectManager::addParticle(string key, float z, float x, float y, float angle, int count, bool isAlpha, BYTE alpha)
{
    tagParticle ptcle;
    ptcle.imgKey = key;
    ptcle.z = z;
    ptcle.x = x - IMAGE->findImage(key)->getFrameWidth() / 2;
    ptcle.y = y - IMAGE->findImage(key)->getFrameHeight() / 2;
    ptcle.angle = angle + DEGREE(RND->getInt(20) - 10);
    ptcle.frameX = RND->getInt(IMAGE->findImage(key)->getMaxFrameX() + 1);
    ptcle.frameY = RND->getInt(IMAGE->findImage(key)->getMaxFrameY() + 1);
    ptcle.isAlpha = isAlpha;
    ptcle.alpha = alpha;
    ptcle.count = RND->getFromInTo(count - 20, count + 20);
    ptcle.speed = 0.2+RND->getInt(100) / 100.0f;
    ptcle.isPlay = false;
    _vParticle.push_back(ptcle);
    return S_OK;
}
