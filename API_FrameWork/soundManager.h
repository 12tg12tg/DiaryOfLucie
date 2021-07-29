#pragma once
#include "singleton.h"
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 100
#define TOTALSOUNDBUFFER SOUNDBUFFER+EXTRACHANNELBUFFER

class soundManager : public Singleton<soundManager>
{
private:
	typedef map<string, FMOD::Sound**>arrSounds;
	typedef map<string, FMOD::Sound**>::iterator arrSoundIter;

	FMOD::System* m_system;
	FMOD::Sound** m_sound;
	FMOD::Channel** m_channel;

	arrSounds m_totalSounds;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);
	
	void play(string keyName, float volume = 1.0f);
	
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//플레이중이냐
	bool isPlaySound(string keyName);
	//일시정지 중이냐
	bool isPauseSound(string keyName);


	//내가만들어보자 볼륨업/다운
	void setVolume(string keyName, float vol);
	//---------------------------
};

