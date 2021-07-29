#include "framework.h"
#include "txtData.h"

txtData::txtData()
{
}

txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::txtSave(char* saveFileName, vector<string> vStr)
{
	HANDLE file;
	char str[5000];
	DWORD write;

	strncpy_s(str, 5000, vectorArrayCombine(vStr), 5000);
	file = CreateFile(
		saveFileName,
		GENERIC_WRITE,	//권한
		0,				//파일공유모드입력
		NULL,			//보안특성
		CREATE_ALWAYS,	//취할행동
		FILE_ATTRIBUTE_NORMAL, //열때가지게될특성
		NULL);				//세이브시 만들어질 파일에 대한 템플릿파일핸들
	WriteFile(file, str, 5000, &write, NULL);
	CloseHandle(file);	//항상닫자
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[5000];
	ZeroMemory(str, sizeof(str));

	
	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 5000, vArray[i].c_str(), 5000);

		if ((i + 1) < vArray.size())
		{
			strcat(str, ",");
		}
	}
	return str;
}

vector<string> txtData::txtLoad(char* loadFileName)
{
	HANDLE file;
	char str[5000];
	DWORD read;
	
	
	ZeroMemory(str, sizeof(str));

	file = CreateFile(
		loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, str, 5000, &read, NULL);
	CloseHandle(file);

	return charArraySeperation(str);
}

vector<string> txtData::charArraySeperation(char charArray[])
{
	vector<string> vArray;
	char* seperator = ",";
	char* token;
	token = strtok(charArray, seperator);
	vArray.push_back(token);
	while (NULL != (token = strtok(NULL, seperator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
