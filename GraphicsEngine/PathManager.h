///���ҽ� ��θ� �о���� Ŭ����.
///�Ƹ� ��Ʈ���̶� ���� �޾ƿõ�?
#pragma once
#include <Windows.h>
class PathManager
{


public:
	typedef enum PATHNAME
	{
		EX,
		END
	};

	// ���� ���丮
	WCHAR originPath[MAX_PATH];
	PWCHAR pPath;

	//�ӽ� ���
	WCHAR examplePath[MAX_PATH];

	void Init();

	char* GetResourcePath(int _scene);
	//const char* GetSoundPath(const char* _path);
};

