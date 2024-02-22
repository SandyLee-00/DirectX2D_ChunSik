/// <summary>
/// 게임프로세스
/// 게임엔진의 루프를 담당
/// 7.20 lina
/// </summary>
#pragma once
#include <windows.h>
#include "GraphicsEngine.h"
#include "SoundManager.h"
class GameProcess
{
	HWND m_hWnd;
	MSG m_Msg;
	GraphicsEngine* grahicsEngine;
	/// 27일날 추가한 것 빼서 걍 엔진에 박을거다
	//To do : exobj,DrawObj ,PathManager 삭제할것 삭제했는데 자꾸 생긴다 시벌머지

	///파일 경로 읽기
	std::filesystem::path basePath; //내가 찾을 경로
	std::filesystem::path nowPath; //현재경로
	std::filesystem::path relativePath; //상대경로를 구했다!!
public:
	GameProcess();
	~GameProcess();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	HRESULT Initialize(HINSTANCE hInstance);
	void Loop();
	void Finalize();

	//이미지를 불러오는 파일
	std::wstring GetFilePath(std::filesystem::path _path);
	void GetAllResources();
};
