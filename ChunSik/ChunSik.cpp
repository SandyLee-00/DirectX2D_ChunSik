#include <windows.h>
#include "GameProcess.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameProcess* game = new GameProcess();
	game->Initialize(hInstance);
	game->Loop();
	game->Finalize();

	delete game;

	return 0; ///(int) msg.wParm 대체가능
}