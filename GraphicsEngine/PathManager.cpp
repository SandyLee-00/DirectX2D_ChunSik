#include "PathManager.h"

void PathManager::Init()
{
	GetCurrentDirectoryW(MAX_PATH, originPath);
	pPath = wcsstr(originPath, L"\\ChunSik");

	//경고	C28182	NULL 포인터를 역참조하고 있습니다
	if (pPath != nullptr)
	{
		while (*pPath != L'\0')
		{
			*pPath = '\0';
			pPath++;
		}
	}

	for (int i = 0; originPath[i] != '\0'; i++)
	{
		originPath[i] = examplePath[i];
	}

	wcscat_s(examplePath, MAX_PATH, L"..\\ChunSik\\4_Resources\\example\\");
}

char* PathManager::GetResourcePath(int _scene)
{
	char dest[MAX_PATH] = { 0 };
	size_t sz;

	switch (_scene)
	{
	case EX:
		wcstombs_s(&sz, dest, MAX_PATH, examplePath, MAX_PATH);
	default:
		break;
	}


	return dest;
}
