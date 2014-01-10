#ifdef NEKOENGINE_EXPORTS
#define NEKO_API __declspec(dllexport)
#else
#define NEKO_API __declspec(dllimport)
#endif

#define PI 3.1415
 
NEKO_API double PowerOf2 (double UserNumber);
NEKO_API double PowerOf3 (double UserNumber);
NEKO_API double CircleArea (double UserRadius);
NEKO_API double CircleCircum (double UserRadius);
