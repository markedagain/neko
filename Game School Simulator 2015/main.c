/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "../AlphaEngine/AEEngine.h"
#include "../NekoEngine/game.h"
#include "../NekoEngine/space.h"
#include "test.h"
#include "../NekoEngine/neko.h"

#pragma comment (lib, "../lib/Alpha_Engine.lib")
#pragma comment (lib, "../lib/neko.lib")

int gGameRunning = 1;
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR commandLine, int show) {
  GAME *game;
  SPACE *space;
  ENTITY *player;

  AESysInitInfo sysInitInfo;
  sysInitInfo.mAppInstance    = instanceH;
  sysInitInfo.mShow        = show;
  sysInitInfo.mWinWidth      = 800;
  sysInitInfo.mWinHeight      = 600;
  sysInitInfo.mCreateConsole    = 1;
  sysInitInfo.mMaxFrameRate    = 60;
  sysInitInfo.mpWinCallBack    = NULL;//MyWinCallBack;
  sysInitInfo.mClassStyle      = CS_HREDRAW | CS_VREDRAW;
  sysInitInfo.mWindowStyle    = WS_OVERLAPPEDWINDOW;//WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;;
  AESysInit (&sysInitInfo);

  game = game_create();
  space = game_addSpace(game, "main");
  player = space_addEntity(space, arch_test, "player");
  
  AESysReset();

  AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f);
  AEGfxSetBlendMode(AE_GFX_BM_BLEND);
  while(gGameRunning)
  {
    AESysFrameStart();
    AEInputUpdate();

    game_update(game);
    game_draw(game);
    AESysFrameEnd();

    if (AEInputCheckTriggered(VK_ESCAPE) || 0 == AESysDoesWindowExist())
      gGameRunning = 0;
  }

  AESysExit();

  return 1;
}
