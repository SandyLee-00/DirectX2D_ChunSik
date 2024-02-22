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

	// 메인 뷰에 보이는 스프라이트
	Sprite* pMainSprite = nullptr;

	// 애니메이션 뷰에 보이는 스프라이트
	Sprite* pAnimationViewSprite = nullptr;

	// 메인 스프라이트의 이름
	std::wstring pMainSpriteName = {};
	// 추출한 스프라이트들
	std::vector<ExtractedSprite*> extractedSprites = {};
	// 메인 뷰의 렌더 타겟
	CRenderTarget* pRT = nullptr;
	// 여러 스프라이트들을 저장할 용도로 만들긴 했는데 사실 잘 사용안해서 나중에 리팩토링해야 함
	std::unordered_map<std::wstring, Sprite*> sprites = {};

	// 메인 뷰 클래스 (메인 이미지가 보이는)
	CSpriteToolView* pMainView = nullptr;

	// 스프라이트의 정보를 보여줄 뷰 클래스
	SpriteInfoView* pSpriteInfoView = nullptr;

	// 다중 선택
	std::queue<ExtractedSprite*> selectedBoxQueue{};

	// 애니메이션 리스트
	std::vector<SpriteAnimation*> animations = {};

	ResourceManager();
	~ResourceManager();

	void SaveSpriteData(const CString& _filePath);
	void LoadSpriteData(const CString& _filePath);

	void SaveAnimationData(const CString& _filePath);
	void LoadAnimationData(const CString& _filePath);

	// 하나의 애니메이션만 저장. 이 경우 로드는 구현 안 할듯.
	void SaveAnimationOneData(const CString& _filePath, int _idx);

	void ClearAnimations();

};