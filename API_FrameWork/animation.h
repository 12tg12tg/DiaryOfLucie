#pragma once
class animation
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

	_vFrameList _frameList;		//프레임 위치 목록
	_vPlayList _playList;		//플레이 목록

	int _frameNum;				//프레임 갯수
	int _frameWidth;
	int _frameHeight;

	bool _loop;
	bool _play;

	float _frameUpdateSec;
	float _elapseSec;			//프레임 경과시간
	DWORD _nowPlayIndex;		//현재플레이중인 인덱스



public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	//처음부터 끝까지 애니메이션 셋팅
	void setDefPlayFrame(bool reverse = false, bool loop = false);
	//배열에 담겨져 있는 정보만 돌린다.
	void setPlayFrame(int* playArr, int arrLen, bool loop = false);
	//시작과 구간 정해서 돌린다.
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	//초당 갱신 횟수
	void setFPS(int framePerSec);
	//프레임 업데이트 타임
	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline bool isPlay()const { return _play; }
	inline POINT getFramePos()const { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth()const { return _frameWidth; }
	inline int getFrameHeight()const { return _frameHeight; }
};

