#ifndef MENU_ASSETS_H
#define MENU_ASSETS_H

#include "../../../engine/core/include/AssetGroup.h"
#include "../../../engine/core/include/QuadTexture2D.h"
#include "../../../engine/core/include/QuadTextureRegion2D.h"
#include "../../../engine/core/include/Sound.h"
#include "../../../engine/core/include/Music.h"

class MenuAssets : public AssetGroup {
public:
    std::shared_ptr<Texture2D> tUI;
    std::shared_ptr<Texture2D> tMainLogo;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsMainLogo;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton1x1Idle;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton1x1Pressed;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton1x1Disabled;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton1x1_5Idle;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton1x1_5Pressed;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton1x1_5Disabled;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton2x2Idle;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton2x2Pressed;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton2x2Disabled;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton4x2Idle;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton4x2Pressed;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsButton4x2Disabled;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsPlayIdle;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsPlayPressed;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsPlayDisabled;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsSettingsIdle;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsSettingsPressed;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsSettingsDisabled;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsExitIdle;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsExitPressed;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsExitDisabled;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsPauseIdle;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsPausePressed;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsPauseDisabled;
    //std::shared_ptr<QuadTexture2D> qGameGB;
    std::shared_ptr<QuadTextureRegion2D> qTRImageView;
    std::shared_ptr<QuadTextureRegion2D> qTRButton;
    std::shared_ptr<QuadTextureRegion2D> qTRMainLogo;
    std::shared_ptr<Texture2DShader> shScene;
    std::shared_ptr<Music> mMenu;

    MenuAssets();
    virtual ~MenuAssets() override;
};

#endif