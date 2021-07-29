#pragma once
#include "singleton.h"

class txtData : public Singleton<txtData>
{
public:
	txtData();
	~txtData();

	HRESULT init();
	
	//���̺�
	void txtSave(char* saveFileName, vector<string>vStr);
	char* vectorArrayCombine(vector<string>vArray);

	//�ε�
	//���ٿ� ���� ������
	vector<string>txtLoad(char* loadFileName);
	//�����͵��� ����Ʈ
	vector<string> charArraySeperation(char charArray[]);


private:

};

