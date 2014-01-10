#ifndef __NEKO_H__
#define __NEKO_H__

#ifdef NEKOENGINE_EXPORTS
#define NEKO_API __declspec(dllexport)
#else
#define NEKO_API __declspec(dllimport)
#endif

#endif