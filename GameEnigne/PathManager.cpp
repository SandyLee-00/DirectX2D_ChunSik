#include "PathManager.h"

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

/// <summary>
/// ��� �Ŵ��� �ʱ�ȭ
/// </summary>
void PathManager::Initalize()
{
	// ���� ��θ� �޾ƿ´�
	nowPath = std::filesystem::current_path();

	// �θ��Ǻθ��Ǻθ� ��θ� �����´�
	headPath = nowPath.parent_path();
	/*headPath = headPath.parent_path();
	headPath = headPath.parent_path();*/

	// ���ҽ� ��ġ�� �̵�

	resDirName = L"\\Resources\\";
	OutputDebugString((headPath.c_str() + resDirName).c_str());
	OutputDebugString(L"\n");
}

/// <summary>
/// ���ҽ� ��� ����
/// </summary>
/// <param name="_string">�߰� ���</param>
/// <returns>������ ���� ���</returns>
std::wstring PathManager::GetResourcePath(const std::wstring& _string)
{
	std::wstring total = nowPath.c_str() + resDirName + _string;
	return total;
}
