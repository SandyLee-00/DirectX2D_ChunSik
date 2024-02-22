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
/// 리소스 매니져 초기화
/// </summary>
/// <param name="_graphicsEngine"></param>
void ResourceManager::Initalize(GraphicsEngine* _graphicsEngine)
{
	this->grapicsEngine = _graphicsEngine;
}

/// <summary>
/// 이미지 로드
/// </summary>
/// <param name="_key">키 값</param>
/// <param name="_path">경로</param>
void ResourceManager::LoadImage(const std::string& _key, const std::wstring& _path)
{
	// 만일 이미지 맵에 있는 정보라면 로드 무시
	if (this->imageMap.find(_key) != this->imageMap.end())
	{
		return;
	}

	// 그래픽 엔진에서 이미지 로드 후 아이디 받아오기
	this->imageMap.insert({ _key, this->grapicsEngine->LoadSpriteSheet(_path.c_str()) });
}

/// <summary>
/// 이미지 아이디 가져오기
/// </summary>
/// <param name="_key">키값</param>
/// <returns>이미지 아이디</returns>
int ResourceManager::GetImageId(const std::string& _key)
{
	// 이미지 맵에 있는 아이디 이면
	if (this->imageMap.find(_key) != this->imageMap.end())
	{
		return imageMap[_key];

	}
	// 아니면
	assert(false && "Worng Key to Find Image\n");
	return -1;
}
