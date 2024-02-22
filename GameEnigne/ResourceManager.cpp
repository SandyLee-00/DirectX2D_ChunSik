#include "ResourceManager.h"
#include "GraphicsEngine.h"
ResourceManager::ResourceManager()
	: grapicsEngine(nullptr)
{
}

ResourceManager::~ResourceManager()
{
}

/// <summary>
/// ���ҽ� �Ŵ��� �ʱ�ȭ
/// </summary>
/// <param name="_graphicsEngine"></param>
void ResourceManager::Initalize(GraphicsEngine* _graphicsEngine)
{
	this->grapicsEngine = _graphicsEngine;
}

/// <summary>
/// �̹��� �ε�
/// </summary>
/// <param name="_key">Ű ��</param>
/// <param name="_path">���</param>
void ResourceManager::LoadImage(const std::string& _key, const std::wstring& _path)
{
	// ���� �̹��� �ʿ� �ִ� ������� �ε� ����
	if (this->imageMap.find(_key) != this->imageMap.end())
	{
		return;
	}

	// �׷��� �������� �̹��� �ε� �� ���̵� �޾ƿ���
	this->imageMap.insert({ _key, this->grapicsEngine->LoadSpriteSheet(_path.c_str()) });
}

/// <summary>
/// �̹��� ���̵� ��������
/// </summary>
/// <param name="_key">Ű��</param>
/// <returns>�̹��� ���̵�</returns>
int ResourceManager::GetImageId(const std::string& _key)
{
	// �̹��� �ʿ� �ִ� ���̵� �̸�
	if (this->imageMap.find(_key) != this->imageMap.end())
	{
		return imageMap[_key];

	}
	// �ƴϸ�
	assert(false && "Worng Key to Find Image\n");
	return -1;
}
