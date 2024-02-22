#pragma once

#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

class Sprite;
class ExtractedSprite;
class CSpriteToolView;
class SpriteInfoView;
class SpriteAnimation;

class ResourceManager
{
public:

	// ���� �信 ���̴� ��������Ʈ
	Sprite* pMainSprite = nullptr;

	// �ִϸ��̼� �信 ���̴� ��������Ʈ
	Sprite* pAnimationViewSprite = nullptr;

	// ���� ��������Ʈ�� �̸�
	std::wstring pMainSpriteName = {};
	// ������ ��������Ʈ��
	std::vector<ExtractedSprite*> extractedSprites = {};
	// ���� ���� ���� Ÿ��
	CRenderTarget* pRT = nullptr;
	// ���� ��������Ʈ���� ������ �뵵�� ����� �ߴµ� ��� �� �����ؼ� ���߿� �����丵�ؾ� ��
	std::unordered_map<std::wstring, Sprite*> sprites = {};

	// ���� �� Ŭ���� (���� �̹����� ���̴�)
	CSpriteToolView* pMainView = nullptr;

	// ��������Ʈ�� ������ ������ �� Ŭ����
	SpriteInfoView* pSpriteInfoView = nullptr;

	// ���� ����
	std::queue<ExtractedSprite*> selectedBoxQueue{};

	// �ִϸ��̼� ����Ʈ
	std::vector<SpriteAnimation*> animations = {};

	ResourceManager();
	~ResourceManager();

	void SaveSpriteData(const CString& _filePath);
	void LoadSpriteData(const CString& _filePath);

	void SaveAnimationData(const CString& _filePath);
	void LoadAnimationData(const CString& _filePath);

	// �ϳ��� �ִϸ��̼Ǹ� ����. �� ��� �ε�� ���� �� �ҵ�.
	void SaveAnimationOneData(const CString& _filePath, int _idx);

	void ClearAnimations();

};