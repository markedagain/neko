/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __NEKO_H__
#define __NEKO_H__

#ifdef NEKOENGINE_EXPORTS
#define NEKO_API __declspec(dllexport)
#else
#define NEKO_API __declspec(dllimport)
#endif

#define NEKO_DEFAULT_FPS 60
#define NEKO_DEFAULT_GAMEWIDTH 640
#define NEKO_DEFAULT_GAMEHEIGHT 360
#define NEKO_DEFAULT_ROOT "data/"
#define NEKO_GAMETITLE "Game School Simulator 2015"

#endif