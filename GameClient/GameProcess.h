#pragma once
#include "GraphicsEngine.h"
#include "ManagerSet.h"
#include <windows.h>
#include "SoundManager.h"


/// <summry>
/// 엔진 데모 및 디버깅을 하기 위한 클래스
/// 최초 작성일 : 2023/07/31
/// 최종 작성일 : 2023/07/31
/// 작성자 : 김형환
/// <\summry>


class GameProcess
{
private:
	// 윈도우 핸들러
	HWND hwnd;
	GraphicsEngine* graphicsEngine;
	ManagerSet* manager;
	bool isDebug;

public:
	// 생성자 소멸자
	GameProcess();
	~GameProcess();

	// 명시적 초기화
	void Initialize(HWND _hwnd);

	// 루프에서 실행되는 함수
	void Process();
private:
	// 실제 수행되는 함수
	void Update();
	void Render();
	void FinalUpdate();

};

