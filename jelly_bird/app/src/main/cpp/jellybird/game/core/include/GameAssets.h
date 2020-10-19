#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include "../../../engine/core/include/AssetGroup.h"
#include "../../../engine/core/include/QuadTexture2D.h"
#include "../../../engine/core/include/QuadTextureRegion2D.h"
#include "../../../engine/core/include/Sound.h"
#include "../../../engine/core/include/Music.h"

class GameAssets : public AssetGroup {
public:
    std::shared_ptr<Texture2D> tBird;
    std::shared_ptr<Texture2D> tGameBGDay;
    std::shared_ptr<Texture2D> tGameBGNight;
    std::shared_ptr<Texture2D> tDirt1x1;
    std::shared_ptr<Texture2D> tGrassDirt1x1;
    std::shared_ptr<Texture2D> tWall;
    std::shared_ptr<Texture2D> tCoins;
    std::shared_ptr<Texture2D> tEnergy;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsBird;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsBirdHit;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsWall;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsGrassDirt1x1;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsDirt1x1;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCoinGold;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCoinSilver;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCoinBronze;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCoinDiamond;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCoinPickGold;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCoinPickSilver;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCoinPickBronze;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCoinPickDiamond;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsElixir;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsElixirPick;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCherry;
    std::vector<std::shared_ptr<TextureRegion2D>> tRsCherryPick;
    std::shared_ptr<QuadTexture2D> qGameGB;
    std::shared_ptr<QuadTextureRegion2D> qTRBird;
    std::shared_ptr<QuadTextureRegion2D> qTRWall;
    std::shared_ptr<QuadTextureRegion2D> qTRGrassDirt1x1;
    std::shared_ptr<QuadTextureRegion2D> qTRDirt1x1;
    std::shared_ptr<QuadTextureRegion2D> qTRCoinGold;
    std::shared_ptr<QuadTextureRegion2D> qTRCoinSilver;
    std::shared_ptr<QuadTextureRegion2D> qTRCoinBronze;
    std::shared_ptr<QuadTextureRegion2D> qTRCoinDiamond;
    std::shared_ptr<QuadTextureRegion2D> qTRAnimationEnd;
    std::shared_ptr<QuadTextureRegion2D> qTRElixir;
    std::shared_ptr<QuadTextureRegion2D> qTRCherry;
    std::shared_ptr<QuadTextureRegion2D> qTRImageView;
    std::shared_ptr<Texture2DShader> shScene;
    std::shared_ptr<Sound> sFlapWings;
    std::shared_ptr<Sound> sGoalReach;
    std::shared_ptr<Sound> sBirdHit;
    std::shared_ptr<Sound> sCoin;
    std::shared_ptr<Sound> sCoin2;
    std::shared_ptr<Sound> sCoin3;
    std::shared_ptr<Sound> sCoin4;
    std::shared_ptr<Sound> sEnergyGainElixir;
    std::shared_ptr<Sound> sEnergyGainCherry;
    std::shared_ptr<Music> mGame;

    GameAssets();
    virtual ~GameAssets() override;
};

#endif