#pragma once
class animation
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

	_vFrameList _frameList;		//������ ��ġ ���
	_vPlayList _playList;		//�÷��� ���

	int _frameNum;				//������ ����
	int _frameWidth;
	int _frameHeight;

	bool _loop;
	bool _play;

	float _frameUpdateSec;
	float _elapseSec;			//������ ����ð�
	DWORD _nowPlayIndex;		//�����÷������� �ε���



public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	//ó������ ������ �ִϸ��̼� ����
	void setDefPlayFrame(bool reverse = false, bool loop = false);
	//�迭�� ����� �ִ� ������ ������.
	void setPlayFrame(int* playArr, int arrLen, bool loop = false);
	//���۰� ���� ���ؼ� ������.
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	//�ʴ� ���� Ƚ��
	void setFPS(int framePerSec);
	//������ ������Ʈ Ÿ��
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

