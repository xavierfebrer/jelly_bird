#ifndef ANDROID_UTIL_H
#define ANDROID_UTIL_H

#include "../../core/include/BaseInclude.h"
#include "../../core/include/Vec2.h"
#include "../../core/include/Rect.h"
#include "../../core/include/PointerInfo.h"
#include "../../core/include/KeyInfo.h"
#include "../../core/include/PointerEventInfo.h"
#include "../../core/include/Util.h"
#include <android_native_app_glue.h>

class AndroidUtil {
public:
    static const unsigned int BUFFER_SIZE;

    static bool loadFileFromAssets(android_app* app, const std::string & path, std::string & result);
    static unsigned char* loadImageFromAssets(android_app* app, char const * filename, int * x, int * y, int * comp, int req_comp, bool flipOnLoad);
};

#endif