#ifndef ANDROIDGRAPHICS_H
#define ANDROIDGRAPHICS_H

#include "../../core/include/Graphics.h"
#include <android_native_app_glue.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES3/gl32.h>

class AndroidGraphics : public Graphics {
public:
    android_app* app;
    ANativeWindow * window;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    const EGLint attribList[9] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8,
                                  EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_NONE};
    /*EGLint attribList[] = {
                    EGL_RED_SIZE,       5,
                    EGL_GREEN_SIZE,     6,
                    EGL_BLUE_SIZE,      5,
                    EGL_ALPHA_SIZE,     ( flags & ES_WINDOW_ALPHA ) ? 8 : EGL_DONT_CARE,
                    EGL_DEPTH_SIZE,     ( flags & ES_WINDOW_DEPTH ) ? 8 : EGL_DONT_CARE,
                    EGL_STENCIL_SIZE,   ( flags & ES_WINDOW_STENCIL ) ? 8 : EGL_DONT_CARE,
                    EGL_SAMPLE_BUFFERS, ( flags & ES_WINDOW_MULTISAMPLE ) ? 1 : 0,
                    // if EGL_KHR_create_context extension is supported, then we will use
                    // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
                    EGL_RENDERABLE_TYPE, GetContextRenderableType ( esContext->eglDisplay ),
                    EGL_NONE
            };*/

    EGLConfig config;
    EGLint numConfigs;
    EGLint format;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLint contextAttribs[3] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

    AndroidGraphics(android_app* app);
    virtual ~AndroidGraphics() override;

    virtual bool init() override;
    virtual BaseComponentReadiness isReady() override;

    virtual bool onWindowInit(ANativeWindow * wind);
    virtual bool onWindowTerm();
    virtual void onResizeEvent() override;
    virtual void resume() override;
    virtual void pause() override;
    virtual void startUpdate(double deltaTime) override;
    virtual void endUpdate(double deltaTime) override;
    virtual void startRender(double deltaTime) override;
    virtual void clearScreen(float a, float r, float g, float b) override;
    virtual void clearScreen(const Color & color) override;
    virtual void endRender(double deltaTime) override;
    virtual Vec2<int> getWindowSize() override;
protected:
    virtual bool initEGL();

    bool initWindow(ANativeWindow * wind);
    bool initSurface();
    bool initContext();
    void destroySurface();
    void destroy();
};

#endif