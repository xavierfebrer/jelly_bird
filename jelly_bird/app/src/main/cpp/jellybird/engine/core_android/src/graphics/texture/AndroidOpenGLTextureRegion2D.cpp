#include "../../../include/AndroidOpenGLTextureRegion2D.h"
#include "../../../include/AndroidUtil.h"

AndroidOpenGLTextureRegion2D::AndroidOpenGLTextureRegion2D(android_app * app, AndroidOpenGLTexture2D * texture2D,
                                                           int x, int y, int w, int h)
        : TextureRegion2D(texture2D, x, y, w, h), app(app) {
}

AndroidOpenGLTextureRegion2D::AndroidOpenGLTextureRegion2D(android_app * app, AndroidOpenGLTexture2D * texture2D,
                                                           const Rect<int> & region)
        : TextureRegion2D(texture2D, region), app(app) {

}

AndroidOpenGLTextureRegion2D::~AndroidOpenGLTextureRegion2D() {
    unLoad();
}

bool AndroidOpenGLTextureRegion2D::load() {
    if(!loaded) {
        loaded = true;
    }
    return loaded;
}

bool AndroidOpenGLTextureRegion2D::unLoad() {
    if(loaded) {
        loaded = false;
    }
    return !loaded;
}
