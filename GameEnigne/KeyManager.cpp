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
/// Ű ���� ������Ʈ
/// ���콺 ��ġ ������Ʈ
/// </summary>
void KeyManager::Update()
{
	// ���� ��Ŀ�� [X] ���¸� Ű ��ü �� ���� ó���ϱ� / ������ �־����� ����
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

	// ���� ��Ŀ�� [O] �� Ű ���� ������Ʈ
	for (size_t i = 0; i < (size_t)KEY::END; ++i)
	{
		// Ű�� �����ִ�
		if (GetAsyncKeyState(virtualKeyArray[i]) & 0x8000)
		{
			if (keyInfomation[i].prevPush)
			{
				// �������� ���� �־���.
				keyInfomation[i].state = KEY_STATE::HOLD;
			}
			else
			{
				// ������ �������� �ʾҴ�.
				keyInfomation[i].state = KEY_STATE::DOWN;
			}

			keyInfomation[i].prevPush = true;
		}

		// Ű�� �ȴ����ִ�
		else
		{
			if (keyInfomation[i].prevPush)
			{
				// ������ ���� �־���.
				keyInfomation[i].state = KEY_STATE::UP;
			}
			else
			{
				// �������� �������� �ʾҴ�.
				keyInfomation[i].state = KEY_STATE::NONE;
			}

			keyInfomation[i].prevPush = false;
		}
	}
	// ���콺 ��ġ ������Ʈ
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(hwnd, &mousePoint);

	mousePosition.x = (float)mousePoint.x;
	mousePosition.y = (float)mousePoint.y;
}

/// <summary>
/// Ű ���� ����
/// </summary>
void KeyManager::Reset()
{
	for (size_t i = 0; i < (size_t)KEY::END; i++)
	{
		keyInfomation[i].state = KEY_STATE::NONE;
		keyInfomation[i].prevPush = false;
	}
}
