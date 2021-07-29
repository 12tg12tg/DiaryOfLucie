#include "framework.h"
#include "soundManager.h"

soundManager::soundManager() : m_system(nullptr), m_channel(nullptr), m_sound(nullptr)
{
}

soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
    FMOD::System_Create(&m_system); //����ý��ۻ���

    m_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

    m_sound = new FMOD::Sound * [TOTALSOUNDBUFFER];
    m_channel = new FMOD::Channel* [TOTALSOUNDBUFFER];

    memset(m_sound, 0, sizeof(FMOD::Sound*) * (TOTALSOUNDBUFFER));
    memset(m_channel, 0, sizeof(FMOD::Channel*) * (TOTALSOUNDBUFFER));


    return S_OK;
}

void soundManager::release()
{
    if ((m_channel != nullptr) | (m_sound != nullptr))
    {
        for (size_t i = 0; i < TOTALSOUNDBUFFER; i++)
        {
            if (m_channel != nullptr)
            {
                if (m_channel[i])m_channel[i]->stop();
            }
            if (m_sound != nullptr)
            {
                if (m_sound[i])m_sound[i]->release();
            }
        }
    }
    SAFE_DELETE(m_channel);
    SAFE_DELETE(m_sound);
    
    //�ý��� ����
    if (m_system != nullptr)
    {
        m_system->release();
        m_system->close();

    }
}

void soundManager::update()
{
    m_system->update();
}

void soundManager::render()
{
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
    if (loop)
    {
        if (bgm)//���
        {
            m_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_sound[m_totalSounds.size()]);
        }
        else
        {
            m_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_sound[m_totalSounds.size()]);
        }
    }
    else
    {
        m_system->createSound(soundName.c_str(), FMOD_DEFAULT, nullptr, &m_sound[m_totalSounds.size()]);

    }
    m_totalSounds.insert(make_pair(keyName, &m_sound[m_totalSounds.size()]));
}

void soundManager::play(string keyName, float volume)
{
    int count = 0;
    
    arrSoundIter iter = m_totalSounds.begin();
    for (iter; iter != m_totalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            //�����Ű�±���
            m_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_channel[count]);
            m_channel[count]->setVolume(volume);
        }
    }

}

void soundManager::stop(string keyName)
{
    int count = 0;

    arrSoundIter iter = m_totalSounds.begin();
    for (iter; iter != m_totalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            m_channel[count]->stop();
            break;
        }
    }
}

void soundManager::pause(string keyName)
{
    int count = 0;

    arrSoundIter iter = m_totalSounds.begin();
    for (iter; iter != m_totalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            m_channel[count]->setPaused(true);
            break;
        }
    }
}

void soundManager::resume(string keyName)
{
    int count = 0;

    arrSoundIter iter = m_totalSounds.begin();
    for (iter; iter != m_totalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            m_channel[count]->setPaused(false);
            break;
        }
    }
}

bool soundManager::isPlaySound(string keyName)
{
    int count = 0;
    bool isPlay;
    arrSoundIter iter = m_totalSounds.begin();
    for (iter; iter != m_totalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            m_channel[count]->isPlaying(&isPlay);
            break;
        }
    }
    return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
    int count = 0;
    bool isPause;
    arrSoundIter iter = m_totalSounds.begin();
    for (iter; iter != m_totalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            m_channel[count]->getPaused(&isPause);
            break;
        }
    }
    return isPause;
}

void soundManager::setVolume(string keyName, float volume)
{
    int count = 0;
    arrSoundIter iter = m_totalSounds.begin();
    for (iter; iter != m_totalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            m_channel[count]->setVolume(volume);
            break;
        }
    }
}
