#include "KeyManager.h"

#include "Vector2.h"

KeyManager::KeyManager()
	: keyInfomation(),
	hwnd(nullptr),
	mousePosition(Vector2(0, 0))
{
	
}

KeyManager::~KeyManager()
{

}

void KeyManager::Initalize(HWND _hwnd)
{
	hwnd = _hwnd;

	for (UINT i = 0; i < (UINT)KEY::END; i++)
	{
		keyInfomation[i] = tKeyInfo{ KEY_STATE::NONE, false };
	}
}

/// <summary>
/// 키 상태 업데이트
/// 마우스 위치 업데이트
/// </summary>
void KeyManager::Update()
{
	// 게임 포커스 [X] 상태면 키 전체 안 누름 처리하기 / 누르고 있었으면 떼기
	HWND isGetFocusedHwnd = GetFocus();

	if (isGetFocusedHwnd == nullptr)
	{
		for (size_t i = 0; i < (size_t)KEY::END; i++)
		{
			keyInfomation[i].prevPush = false;

			if (keyInfomation[i].state == KEY_STATE::DOWN || keyInfomation[i].state == KEY_STATE::HOLD)
			{
				keyInfomation[i].state = KEY_STATE::UP;
			}
			if (keyInfomation[i].state == KEY_STATE::UP)
			{
				keyInfomation[i].state = KEY_STATE::NONE;
			}
		}
		return;
	}

	// 게임 포커스 [O] 때 키 상태 업데이트
	for (size_t i = 0; i < (size_t)KEY::END; ++i)
	{
		// 키가 눌려있다
		if (GetAsyncKeyState(virtualKeyArray[i]) & 0x8000)
		{
			if (keyInfomation[i].prevPush)
			{
				// 이전에도 눌려 있었다.
				keyInfomation[i].state = KEY_STATE::HOLD;
			}
			else
			{
				// 이전에 눌려있지 않았다.
				keyInfomation[i].state = KEY_STATE::DOWN;
			}

			keyInfomation[i].prevPush = true;
		}

		// 키가 안눌려있다
		else
		{
			if (keyInfomation[i].prevPush)
			{
				// 이전에 눌려 있었다.
				keyInfomation[i].state = KEY_STATE::UP;
			}
			else
			{
				// 이전에도 눌려있지 않았다.
				keyInfomation[i].state = KEY_STATE::NONE;
			}

			keyInfomation[i].prevPush = false;
		}
	}
	// 마우스 위치 업데이트
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(hwnd, &mousePoint);

	mousePosition.x = (float)mousePoint.x;
	mousePosition.y = (float)mousePoint.y;
}

/// <summary>
/// 키 상태 리셋
/// </summary>
void KeyManager::Reset()
{
	for (size_t i = 0; i < (size_t)KEY::END; i++)
	{
		keyInfomation[i].state = KEY_STATE::NONE;
		keyInfomation[i].prevPush = false;
	}
}
