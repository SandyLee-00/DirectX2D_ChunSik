#include "PathManager.h"

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

/// <summary>
/// 경로 매니져 초기화
/// </summary>
void PathManager::Initalize()
{
	// 현재 경로를 받아온다
	nowPath = std::filesystem::current_path();

	// 부모의부모의부모 경로를 가져온다
	headPath = nowPath.parent_path();
	/*headPath = headPath.parent_path();
	headPath = headPath.parent_path();*/

	// 리소스 위치로 이동

	resDirName = L"\\Resources\\";
	OutputDebugString((headPath.c_str() + resDirName).c_str());
	OutputDebugString(L"\n");
}

/// <summary>
/// 리소스 경로 리턴
/// </summary>
/// <param name="_string">추가 경로</param>
/// <returns>합쳐진 최종 경로</returns>
std::wstring PathManager::GetResourcePath(const std::wstring& _string)
{
	std::wstring total = nowPath.c_str() + resDirName + _string;
	return total;
}
