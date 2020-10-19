#include "../../include/AndroidMenuAssets.h"

AndroidMenuAssets::AndroidMenuAssets(android_app * app) : MenuAssets(), app(app) {
    createResources();
}

AndroidMenuAssets::~AndroidMenuAssets() {
    unLoad();
}

bool AndroidMenuAssets::load() {
    if(!loaded) {
        std::cout << "---> load AndroidMenuAssets" << std::endl;

        for(auto & resource : resources) {
            resource->load();
        }
        loaded = true;
    }
    return loaded;
}

bool AndroidMenuAssets::unLoad() {
    if(loaded) {
        std::cout << "---> unLoad AndroidMenuAssets" << std::endl;

        for(auto & resource : resources) {
            resource->unLoad();
        }
        loaded = false;
    }
    return !loaded;
}

void AndroidMenuAssets::createResources() {

    // texture2D
    auto aOGLTUI = std::make_shared<AndroidOpenGLTexture2D>(app, Assets::PATH_IMAGE + "ui.png",
                                                            true, 0, GL_NEAREST, GL_NEAREST,
                                                            GL_REPEAT, GL_REPEAT, 0,
                                                            GL_UNSIGNED_BYTE, true);
    tUI = aOGLTUI;
    resources.push_back(tUI);
    auto aOGLTMainLogo = std::make_shared<AndroidOpenGLTexture2D>(app, Assets::PATH_IMAGE +
                                                                       "main_logo.png", true, 0,
                                                                  GL_NEAREST, GL_NEAREST, GL_REPEAT,
                                                                  GL_REPEAT, 0, GL_UNSIGNED_BYTE,
                                                                  true);
    tMainLogo = aOGLTMainLogo;
    resources.push_back(tMainLogo);

    // texture region 2D
    Vec2<double> buttonSize;
    double y;

    buttonSize.set(16 * 1, 16 * 1);
    y = 0;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonIdle = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                           x * buttonSize.x,
                                                                           y * buttonSize.y,
                                                                           buttonSize.x,
                                                                           buttonSize.y);
        tRsButton1x1Idle.push_back(tRButtonIdle);
        resources.push_back(tRButtonIdle);
    }
    y = 1;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonPressed = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                              x * buttonSize.x,
                                                                              y * buttonSize.y,
                                                                              buttonSize.x,
                                                                              buttonSize.y);
        tRsButton1x1Pressed.push_back(tRButtonPressed);
        resources.push_back(tRButtonPressed);
    }
    y = 2;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonDisabled = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                               x * buttonSize.x,
                                                                               y * buttonSize.y,
                                                                               buttonSize.x,
                                                                               buttonSize.y);
        tRsButton1x1Disabled.push_back(tRButtonDisabled);
        resources.push_back(tRButtonDisabled);
    }

    buttonSize.set(16 * 1.5, 16 * 1.5);
    y = 0;
    auto tRButtonIdle = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                       16 + buttonSize.x * 0,
                                                                       y * buttonSize.y,
                                                                       buttonSize.x,
                                                                       buttonSize.y);
    tRsButton1x1_5Idle.push_back(tRButtonIdle);
    resources.push_back(tRButtonIdle);
    auto tRButtonPressed = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                          16 + buttonSize.x * 1,
                                                                          y * buttonSize.y,
                                                                          buttonSize.x,
                                                                          buttonSize.y);
    tRsButton1x1_5Pressed.push_back(tRButtonPressed);
    resources.push_back(tRButtonPressed);
    auto tRButtonDisabled = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                           16 + buttonSize.x * 2,
                                                                           y * buttonSize.y,
                                                                           buttonSize.x,
                                                                           buttonSize.y);
    tRsButton1x1_5Disabled.push_back(tRButtonDisabled);
    resources.push_back(tRButtonDisabled);

    buttonSize.set(16 * 2, 16 * 2);
    y = 1.50;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonIdle = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                           x * buttonSize.x,
                                                                           y * buttonSize.y,
                                                                           buttonSize.x,
                                                                           buttonSize.y);
        tRsButton2x2Idle.push_back(tRButtonIdle);
        resources.push_back(tRButtonIdle);
    }
    y = 2.5;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonPressed = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                              x * buttonSize.x,
                                                                              y * buttonSize.y,
                                                                              buttonSize.x,
                                                                              buttonSize.y);
        tRsButton2x2Pressed.push_back(tRButtonPressed);
        resources.push_back(tRButtonPressed);
    }
    y = 3.5;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonDisabled = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                               x * buttonSize.x,
                                                                               y * buttonSize.y,
                                                                               buttonSize.x,
                                                                               buttonSize.y);
        tRsButton2x2Disabled.push_back(tRButtonDisabled);
        resources.push_back(tRButtonDisabled);
    }

    buttonSize.set(16 * 4, 16 * 2);
    y = 4.5;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonIdle = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                           x * buttonSize.x,
                                                                           y * buttonSize.y,
                                                                           buttonSize.x,
                                                                           buttonSize.y);
        tRsButton4x2Idle.push_back(tRButtonIdle);
        resources.push_back(tRButtonIdle);
    }
    y = 5.5;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonPressed = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                              x * buttonSize.x,
                                                                              y * buttonSize.y,
                                                                              buttonSize.x,
                                                                              buttonSize.y);
        tRsButton4x2Pressed.push_back(tRButtonPressed);
        resources.push_back(tRButtonPressed);
    }
    y = 6.5;
    for(int x = 0; x < 1; ++x) {
        auto tRButtonDisabled = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                               x * buttonSize.x,
                                                                               y * buttonSize.y,
                                                                               buttonSize.x,
                                                                               buttonSize.y);
        tRsButton4x2Disabled.push_back(tRButtonDisabled);
        resources.push_back(tRButtonDisabled);
    }

    y = 0;
    Vec2<int> mainLogoSize(16 * 2, 16 * 2);
    for(int x = 0; x < 4; ++x) {
        auto tRMainLogo = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTMainLogo.get(),
                                                                         x * mainLogoSize.x,
                                                                         y * mainLogoSize.y,
                                                                         mainLogoSize.x,
                                                                         mainLogoSize.y);
        tRsMainLogo.push_back(tRMainLogo);
        resources.push_back(tRMainLogo);
    }
    for(int x = 3; x >= 1; --x) {
        auto tRMainLogo = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTMainLogo.get(),
                                                                         x * mainLogoSize.x,
                                                                         y * mainLogoSize.y,
                                                                         mainLogoSize.x,
                                                                         mainLogoSize.y);
        tRsMainLogo.push_back(tRMainLogo);
        resources.push_back(tRMainLogo);
    }
    for(int x = 4; x < 7; ++x) {
        auto tRMainLogo = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTMainLogo.get(),
                                                                         x * mainLogoSize.x,
                                                                         y * mainLogoSize.y,
                                                                         mainLogoSize.x,
                                                                         mainLogoSize.y);
        tRsMainLogo.push_back(tRMainLogo);
        resources.push_back(tRMainLogo);
    }
    for(int x = 5; x >= 4; --x) {
        auto tRMainLogo = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTMainLogo.get(),
                                                                         x * mainLogoSize.x,
                                                                         y * mainLogoSize.y,
                                                                         mainLogoSize.x,
                                                                         mainLogoSize.y);
        tRsMainLogo.push_back(tRMainLogo);
        resources.push_back(tRMainLogo);
    }

    std::shared_ptr<AndroidOpenGLTextureRegion2D> tRIcon;
    Vec2<int> iconSize(16 * 1, 16 * 1);
    y = 21;
    for(int x = 0; x < 4; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(),
                                                                     x * iconSize.x, y * iconSize.y,
                                                                     iconSize.x, iconSize.y);
        tRsPlayIdle.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 22;
    for(int x = 0; x < 4; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsPlayPressed.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 23;
    for(int x = 0; x < 4; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsPlayDisabled.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 24;
    for(int x = 0; x < 2; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsSettingsIdle.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 25;
    for(int x = 0; x < 2; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsSettingsPressed.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 26;
    for(int x = 0; x < 2; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsSettingsDisabled.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 27;
    for(int x = 0; x < 4; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsExitIdle.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 28;
    for(int x = 0; x < 4; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsExitPressed.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 29;
    for(int x = 0; x < 4; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsExitDisabled.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 30;
    for(int x = 0; x < 1; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsPauseIdle.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 30;
    for(int x = 1; x < 2; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsPausePressed.push_back(tRIcon);
        resources.push_back(tRIcon);
    }
    y = 30;
    for(int x = 2; x < 3; ++x) {
        tRIcon = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTUI.get(), x * iconSize.x,
                                                                y * iconSize.y, iconSize.x,
                                                                iconSize.y);
        tRsPauseDisabled.push_back(tRIcon);
        resources.push_back(tRIcon);
    }



    // quad2D texture
    /*qGameGB = std::make_shared<AndroidOpenGLQuadTexture2D>();
    resources.push_back(qGameGB);*/

    // quad2D texture region
    qTRImageView = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRImageView);
    qTRButton = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRButton);
    qTRMainLogo = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRMainLogo);

    // shader
    shScene = std::make_shared<AndroidOpenGLTexture2DShader>(
            std::make_shared<AndroidOpenGLShader>(app, Assets::PATH_SHADER + "scene.vs", true,
                                                  GL_VERTEX_SHADER),
            std::make_shared<AndroidOpenGLShader>(app, Assets::PATH_SHADER + "scene.fs", true,
                                                  GL_FRAGMENT_SHADER));
    resources.push_back(shScene);

    // music
    mMenu = std::make_shared<AndroidOpenSLESMusic>(app, Assets::PATH_MUSIC + "menu.wav", true);
    resources.push_back(mMenu);
}
