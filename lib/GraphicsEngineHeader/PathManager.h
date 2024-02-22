///리소스 경로를 읽어오는 클래스.
///아마 비트맵이랑 사운드 받아올듯?
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

	// 현재 디렉토리
	WCHAR originPath[MAX_PATH];
	PWCHAR pPath;

	//임시 경로
	WCHAR examplePath[MAX_PATH];

	void Init();

	char* GetResourcePath(int _scene);
	//const char* GetSoundPath(const char* _path);
};

