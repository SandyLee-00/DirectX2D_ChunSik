#include "pch.h"
#include "ResourceManager.h"
#include "ExtractedSprite.h"
#include "Sprite.h"
#include "SpriteTool2View.h"
#include "InfoView.h"
#include "SpriteAnimation.h"

#include <fstream>
#include <iostream>
#include <bitset>

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::SaveSpriteData(const CString& _filePath)
{
	std::wofstream ofs;
	ofs.open(_filePath/*, std::ios::binary*/);
	ofs << this->extractedSprites.size() << std::endl;
	for (const auto& curSprite : this->extractedSprites)
	{
		/*std::char_traits<std::wstring>::int_type tempInt =
			std::char_traits<std::wstring>::to_int_type(curSprite->name);
		std::bitset<8> binaryName(tempInt);*/
		ofs << curSprite->name << ',';
		ofs << curSprite->left << ',';
		ofs << curSprite->top << ',';
		ofs << curSprite->right << ',';
		ofs << curSprite->bottom << ',';
		ofs << curSprite->pivotX << ',';
		ofs << curSprite->pivotY << ',';
		ofs << std::endl;
	}
	ofs.close();
}

void ResourceManager::LoadSpriteData(const CString& _filePath)
{
	int spriteNum = 0;
	std::wifstream ifs;
	ifs.open(_filePath);
	ifs >> spriteNum;
	for (int i = 0; i < spriteNum; i++)
	{
		std::wstring data{};
		ifs >> data;
		ExtractedSprite* pNewSprite = new ExtractedSprite;

		// 데이터 타입을 정할떄 필요한 인덱스
		int dataIndex = 0;

		// 데이터 모음 중 하나의 데이터
		std::wstring one;
		for (int idx = 0; idx < data.size(); idx++)
		{
			if (data[idx] == ',')
			{
				switch (dataIndex)
				{
					case 0:
						// wstring 타입
						pNewSprite->name = one;
						break;
					case 1:
						// float 타입으로 변환.
						pNewSprite->left = stof(one);
						break;
					case 2:
						pNewSprite->top = stof(one);
						break;
					case 3:
						pNewSprite->right = stof(one);
						break;
					case 4:
						pNewSprite->bottom = stof(one);
						break;
					case 5:
						pNewSprite->pivotX = stof(one);
						break;
					case 6:
						pNewSprite->pivotY = stof(one);
						break;
					default:
						break;
				}

				one = std::wstring();
				dataIndex++;
				continue;
			}
			one += data[idx];
		}
		this->extractedSprites.push_back(pNewSprite);
	}
	ifs.close();
}

void ResourceManager::SaveAnimationData(const CString& _filePath)
{
	std::wofstream ofs;
	ofs.open(_filePath);
	//ofs << this->animations.size() << std::endl;
	for (const auto& anim : this->animations)
	{
		ofs << anim->sprites.size() << std::endl;
		ofs << anim->name << std::endl;
		ofs << anim->delayTime << std::endl;
		for (const auto& curSprite : anim->sprites)
		{
			ofs << curSprite->name << ',';
			ofs << curSprite->left << ',';
			ofs << curSprite->top << ',';
			ofs << curSprite->right << ',';
			ofs << curSprite->bottom << ',';
			ofs << curSprite->pivotX << ',';
			ofs << curSprite->pivotY << ',';
			ofs << std::endl;
		}
	}
	ofs.close();
}

void ResourceManager::LoadAnimationData(const CString& _filePath)
{
	ClearAnimations();
	int animCount = 1;
	std::wifstream ifs;
	ifs.open(_filePath);
	//ifs >> animCount;


	for (int i = 0; i < animCount; i++)
	{
		// 현재 애니메이션의 스프라이트 개수
		int spriteCount = 0;
		ifs >> spriteCount;
		SpriteAnimation* pLoadAnimation = new SpriteAnimation;
		ifs >> pLoadAnimation->name;
		ifs >> pLoadAnimation->delayTime;
		for (int j = 0; j < spriteCount; j++)
		{
			// 데이터
			std::wstring data;
			ifs >> data;
			ExtractedSprite* pNewSprite = new ExtractedSprite;

			// 데이터 타입을 정할떄 필요한 인덱스, 사실 하드 코딩에 가까움
			int dataIndex = 0;

			// 데이터 모음 중 하나의 데이터
			std::wstring one;
			for (int idx = 0; idx < data.size(); idx++)
			{
				if (data[idx] == ',')
				{
					switch (dataIndex)
					{
						case 0:
							// wstring 타입
							pNewSprite->name = one;
							break;
						case 1:
							// float 타입으로 변환.
							pNewSprite->left = stof(one);
							break;
						case 2:
							pNewSprite->top = stof(one);
							break;
						case 3:
							pNewSprite->right = stof(one);
							break;
						case 4:
							pNewSprite->bottom = stof(one);
							break;
						case 5:
							pNewSprite->pivotX = stof(one);
							break;
						case 6:
							pNewSprite->pivotY = stof(one);
							break;
						default:
							break;
					}

					one = std::wstring();
					dataIndex++;
					continue;
				}
				one += data[idx];
			}
			pLoadAnimation->sprites.push_back(pNewSprite);
		}
		this->animations.push_back(pLoadAnimation);
	}
	ifs.close();
}

void ResourceManager::SaveAnimationOneData(const CString& _filePath, int _idx)
{
	SpriteAnimation* pSaveAnim = this->animations[_idx];

	std::wofstream ofs;
	ofs.open(_filePath);

	ofs << pSaveAnim->sprites.size() << std::endl;
	ofs << pSaveAnim->name << std::endl;
	ofs << pSaveAnim->delayTime << std::endl;
	for (const auto& curSprite : pSaveAnim->sprites)
	{
		ofs << curSprite->name << ',';
		ofs << curSprite->left << ',';
		ofs << curSprite->top << ',';
		ofs << curSprite->right << ',';
		ofs << curSprite->bottom << ',';
		ofs << curSprite->pivotX << ',';
		ofs << curSprite->pivotY << ',';
		ofs << std::endl;
	}
	ofs.close();
}

void ResourceManager::ClearAnimations()
{
	for (auto& anim : this->animations)
	{
		delete anim;
		anim = nullptr;
	}
	this->animations.clear();
}
