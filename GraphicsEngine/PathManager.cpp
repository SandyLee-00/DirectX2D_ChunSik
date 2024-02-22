#include "PathManager.h"

void PathManager::Init()
{
	GetCurrentDirectoryW(MAX_PATH, originPath);
	pPath = wcsstr(originPath, L"\\ChunSik");

	//���	C28182	NULL �����͸� �������ϰ� �ֽ��ϴ�
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
