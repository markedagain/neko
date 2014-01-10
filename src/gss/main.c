/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "../alpha/AEEngine.h"
#include "../neko/game.h"
#include "../neko/space.h"
#include "test.h"

#pragma comment (lib, "lib/Alpha_Engine.lib")

int gGameRunning = 1;
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
	GAME *game;
  SPACE *space;
  ENTITY *player;

	// Initialize the system
	AESysInitInfo sysInitInfo;
	sysInitInfo.mAppInstance		= instanceH;
	sysInitInfo.mShow				= show;
	sysInitInfo.mWinWidth			= 800;
	sysInitInfo.mWinHeight			= 600;
	sysInitInfo.mCreateConsole		= 1;
	sysInitInfo.mMaxFrameRate		= 60;
	sysInitInfo.mpWinCallBack		= NULL;//MyWinCallBack;
	sysInitInfo.mClassStyle			= CS_HREDRAW | CS_VREDRAW;
	sysInitInfo.mWindowStyle		= WS_OVERLAPPEDWINDOW;//WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;;
	AESysInit (&sysInitInfo);

	game = game_create();
  space = game_addSpace(game, "main");
  player = space_addEntity(space, arch_test, "player");
	
	// reset the system modules
	AESysReset();

	AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// Game Loop
	while(gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();


		// Handling Input
		AEInputUpdate();

    game_update(game);
		game_draw(game);

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(VK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
		//OutputDebugString("Hello World\n");
  }

	// free the system
	AESysExit();

	return 1;
}
