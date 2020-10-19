#include "../../include/AndroidGraphics.h"

AndroidGraphics::AndroidGraphics(android_app* app) : Graphics(), app(app) {
}

AndroidGraphics::~AndroidGraphics() {
    LOGI("Destroying AndroidGraphics");
    destroy();
}

bool AndroidGraphics::init() {
    if(!initialized) {
        if(!initEGL()) {
            return false;
        }
        initialized = true;
    }
    return true;
}

bool AndroidGraphics::initEGL() {
    LOGI("Initializing AndroidGraphics init");
    return true;
}

BaseComponentReadiness AndroidGraphics::isReady() {
    return isInitialized() ? BaseComponentReadiness::READY : BaseComponentReadiness::NOT_READY;
}

bool AndroidGraphics::onWindowInit(ANativeWindow * wind) {
    return initWindow(wind);
}

bool AndroidGraphics::onWindowTerm() {
    destroy();
    return true;
}

void AndroidGraphics::onResizeEvent() {
    EGLint width, height;
    if(!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
       !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        LOGW("eglQuerySurface() returned error %d", eglGetError());
        return;
    }
    LOGI("onResizeEvent() %d x %d", width, height);
    glViewport(0, 0, width, height);
}

void AndroidGraphics::resume() {
}

void AndroidGraphics::pause() {
}

void AndroidGraphics::startUpdate(double deltaTime) {
}

void AndroidGraphics::endUpdate(double deltaTime) {
}

void AndroidGraphics::startRender(double deltaTime) {
}

void AndroidGraphics::clearScreen(float a, float r, float g, float b) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, a);
}

void AndroidGraphics::clearScreen(const Color & color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, color.a);
}

void AndroidGraphics::endRender(double deltaTime) {
    if(!eglSwapBuffers(display, surface)) {
        EGLint error = eglGetError();
        LOGW("eglSwapBuffers() returned error %d", error);
        if (error == EGL_BAD_SURFACE) {
            initSurface();
        } else if (error == EGL_CONTEXT_LOST || error == EGL_BAD_CONTEXT) {
            destroy();
            initContext();
        }
    }
}

Vec2<int> AndroidGraphics::getWindowSize() {
    EGLint width, height;
    if(!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
       !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        LOGW("eglQuerySurface() returned error %d", eglGetError());
        return Vec2<int>(-1, -1);
    }
    return Vec2<int>(width, height);
}

bool AndroidGraphics::initWindow(ANativeWindow * wind) {
    window = wind;
    if(!initSurface()){
        return false;
    }
    if(!initContext()){
        return false;
    }
    return true;
}

bool AndroidGraphics::initSurface() {
    if((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOGW("eglGetDisplay() returned error %d", eglGetError());
        return false;
    }
    if(!eglInitialize(display, &majorVersion, &minorVersion)) {
        LOGW("eglInitialize() returned error %d", eglGetError());
        return false;
    }
    LOGI("Initializing AndroidGraphics initFullscreen");
    if(!eglChooseConfig(display, attribList, &config, 1, &numConfigs)) {
        LOGW("eglChooseConfig() returned error %d", eglGetError());
        return false;
    }
    if(!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
        LOGW("eglGetConfigAttrib() returned error %d", eglGetError());
        return false;
    }
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);
    if((surface = eglCreateWindowSurface(display, config, window, nullptr)) == EGL_NO_SURFACE) {
        LOGW("eglCreateWindowSurface() returned error %d", eglGetError());
        return false;
    }
    return true;
}

bool AndroidGraphics::initContext() {
    if((context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs)) ==
       EGL_NO_CONTEXT) {
        LOGW("eglCreateContext() returned error %d", eglGetError());
        return false;
    }
    if(!eglMakeCurrent(display, surface, surface, context)) {
        LOGW("eglMakeCurrent() returned error %d", eglGetError());
        return false;
    }

    // init values
    EGLint width, height;
    if(!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
       !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        LOGW("eglQuerySurface() returned error %d", eglGetError());
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, width, height);
    LOGI("AndroidGraphics initContext() %d x %d", width, height);

    return true;
}

void AndroidGraphics::destroySurface() {
    if(surface != EGL_NO_SURFACE) {
        eglDestroySurface(display, surface);
        surface = EGL_NO_SURFACE;
    }
}

void AndroidGraphics::destroy() {
    if(display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if(context != EGL_NO_CONTEXT) {
            eglDestroyContext(display, context);
        }
        if(surface != EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }
        eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    surface = EGL_NO_SURFACE;
    context = EGL_NO_CONTEXT;
}
