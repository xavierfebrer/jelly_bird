#include "../../include/AndroidGameAssets.h"

AndroidGameAssets::AndroidGameAssets(android_app * app) : GameAssets(), app(app) {
    createResources();
}

AndroidGameAssets::~AndroidGameAssets() {
    unLoad();
}

bool AndroidGameAssets::load() {
    if(!loaded) {
        std::cout << "---> load AndroidGameAssets" << std::endl;
        loaded = true;
        for(auto & resource : resources) {
            if(!resource->load()){
                loaded = false;
            }
        }
    }
    return loaded;
}

bool AndroidGameAssets::unLoad() {
    if(loaded) {
        std::cout << "---> unLoad AndroidGameAssets" << std::endl;
        loaded = false;
        bool error = false;
        for(auto & resource : resources) {
            if(!resource->unLoad()){
                error = true;
            }
        }
        return !loaded && !error;
    }
    return !loaded;
}

void AndroidGameAssets::createResources() {

    // texture2D
    auto aOGLTBird = std::make_shared<AndroidOpenGLTexture2D>(app,
                                                              Assets::PATH_IMAGE + "bird.png",
                                                              true, 0, GL_NEAREST, GL_NEAREST,
                                                              GL_REPEAT, GL_REPEAT, 0,
                                                              GL_UNSIGNED_BYTE, true);
    tBird = aOGLTBird;
    resources.push_back(tBird);
    auto aOGLTGameBGDay = std::make_shared<AndroidOpenGLTexture2D>(app, Assets::PATH_IMAGE +
                                                                     "game_bg_day.png", true, 0,
                                                                GL_NEAREST, GL_NEAREST,
                                                                GL_REPEAT, GL_REPEAT, 0,
                                                                GL_UNSIGNED_BYTE, true);
    tGameBGDay = aOGLTGameBGDay;
    resources.push_back(tGameBGDay);
    auto aOGLTGameBGNight = std::make_shared<AndroidOpenGLTexture2D>(app, Assets::PATH_IMAGE +
                                                                     "game_bg_night.png", true, 0,
                                                                GL_NEAREST, GL_NEAREST,
                                                                GL_REPEAT, GL_REPEAT, 0,
                                                                GL_UNSIGNED_BYTE, true);
    tGameBGNight = aOGLTGameBGNight;
    resources.push_back(tGameBGNight);
    auto aOGLTDirt1x1 = std::make_shared<AndroidOpenGLTexture2D>(app, Assets::PATH_IMAGE +
                                                                      "dirt1x1.png", true, 0,
                                                                 GL_NEAREST, GL_NEAREST,
                                                                 GL_REPEAT, GL_REPEAT, 0,
                                                                 GL_UNSIGNED_BYTE, true);
    tDirt1x1 = aOGLTDirt1x1;
    resources.push_back(tDirt1x1);
    auto aOGLTGrassDirt1x1 = std::make_shared<AndroidOpenGLTexture2D>(app, Assets::PATH_IMAGE +
                                                                           "grassdirt1x1.png",
                                                                      true, 0, GL_NEAREST,
                                                                      GL_NEAREST, GL_REPEAT,
                                                                      GL_REPEAT, 0,
                                                                      GL_UNSIGNED_BYTE, true);
    tGrassDirt1x1 = aOGLTGrassDirt1x1;
    resources.push_back(tGrassDirt1x1);
    auto aOGLTWall = std::make_shared<AndroidOpenGLTexture2D>(app,
                                                              Assets::PATH_IMAGE + "wall.png",
                                                              true, 0, GL_NEAREST, GL_NEAREST,
                                                              GL_REPEAT, GL_REPEAT, 0,
                                                              GL_UNSIGNED_BYTE, true);
    tWall = aOGLTWall;
    resources.push_back(tWall);
    auto aOGLTCoin = std::make_shared<AndroidOpenGLTexture2D>(app,
                                                              Assets::PATH_IMAGE + "coins.png",
                                                              true, 0, GL_NEAREST, GL_NEAREST,
                                                              GL_REPEAT, GL_REPEAT, 0,
                                                              GL_UNSIGNED_BYTE, true);
    tCoins = aOGLTCoin;
    resources.push_back(tCoins);
    auto aOGLTEnergy = std::make_shared<AndroidOpenGLTexture2D>(app,
                                                              Assets::PATH_IMAGE + "powerup.png",
                                                              true, 0, GL_NEAREST, GL_NEAREST,
                                                              GL_REPEAT, GL_REPEAT, 0,
                                                              GL_UNSIGNED_BYTE, true);
    tEnergy = aOGLTEnergy;
    resources.push_back(tEnergy);

    // texture region 2D
    Vec2<int> birdSize(32, 32);
    int y = 0;
    for(int x = 0; x < 4; ++x) {
        auto tRBird = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTBird.get(),
                                                                     x * birdSize.x,
                                                                     y * birdSize.y, birdSize.x,
                                                                     birdSize.y);
        tRsBird.push_back(tRBird);
        resources.push_back(tRBird);
    }
    for(int x = 2; x >= 0; --x) {
        auto tRBird = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTBird.get(),
                                                                     x * birdSize.x,
                                                                     y * birdSize.y, birdSize.x,
                                                                     birdSize.y);
        tRsBird.push_back(tRBird);
        resources.push_back(tRBird);
    }
    for(int x = 4; x < 7; ++x) {
        auto tRBird = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTBird.get(),
                                                                     x * birdSize.x,
                                                                     y * birdSize.y, birdSize.x,
                                                                     birdSize.y);
        tRsBird.push_back(tRBird);
        resources.push_back(tRBird);
    }
    for(int x = 5; x >= 4; --x) {
        auto tRBird = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTBird.get(),
                                                                     x * birdSize.x,
                                                                     y * birdSize.y, birdSize.x,
                                                                     birdSize.y);
        tRsBird.push_back(tRBird);
        resources.push_back(tRBird);
    }
    y = 1;
    for(int x = 0; x < 8; ++x) {
        auto tRBirdHit = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTBird.get(),
                                                                        x * birdSize.x,
                                                                        y * birdSize.y, birdSize.x,
                                                                        birdSize.y);
        tRsBirdHit.push_back(tRBirdHit);
        resources.push_back(tRBirdHit);
    }

    Vec2<int> wallSize(45, 270);
    y = 0;
    for(int x = 0; x < 5; ++x) {
        auto tRWall = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTWall.get(),
                                                                     x * wallSize.x,
                                                                     y * wallSize.y, wallSize.x,
                                                                     wallSize.y);
        tRsWall.push_back(tRWall);
        resources.push_back(tRWall);
    }
    for(int x = 3; x >= 1; --x) {
        auto tRWall = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTWall.get(),
                                                                     x * wallSize.x,
                                                                     y * wallSize.y, wallSize.x,
                                                                     wallSize.y);
        tRsWall.push_back(tRWall);
        resources.push_back(tRWall);
    }

    Vec2<int> grassDirtSize(20, 20);
    y = 0;
    for(int x = 0; x < 2; ++x) {
        auto tRGrassDirt = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTGrassDirt1x1.get(),
                                                                          x * grassDirtSize.x,
                                                                          y * grassDirtSize.y, grassDirtSize.x,
                                                                          grassDirtSize.y);
        tRsGrassDirt1x1.push_back(tRGrassDirt);
        resources.push_back(tRGrassDirt);
    }

    Vec2<int> dirtSize(20, 20);
    y = 0;
    for(int x = 0; x < 1; ++x) {
        auto tRDirt = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTDirt1x1.get(),
                                                                     x * dirtSize.x,
                                                                     y * dirtSize.y, dirtSize.x,
                                                                     dirtSize.y);
        tRsDirt1x1.push_back(tRDirt);
        resources.push_back(tRDirt);
    }

    Vec2<int> coinSize(16, 16);
    y = 0;
    for(int x = 0; x < 7; ++x) {
        auto tRCoin = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                     x * coinSize.x,
                                                                     y * coinSize.y, coinSize.x,
                                                                     coinSize.y);
        tRsCoinGold.push_back(tRCoin);
        resources.push_back(tRCoin);
    }
    for(int x = 5; x >= 1; --x) {
        auto tRCoin = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                     x * coinSize.x,
                                                                     y * coinSize.y, coinSize.x,
                                                                     coinSize.y);
        tRsCoinGold.push_back(tRCoin);
        resources.push_back(tRCoin);
    }
    y = 1;
    for(int x = 0; x < 7; ++x) {
        auto tRCoin = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                     x * coinSize.x,
                                                                     y * coinSize.y, coinSize.x,
                                                                     coinSize.y);
        tRsCoinSilver.push_back(tRCoin);
        resources.push_back(tRCoin);
    }
    for(int x = 5; x >= 1; --x) {
        auto tRCoin = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                     x * coinSize.x,
                                                                     y * coinSize.y, coinSize.x,
                                                                     coinSize.y);
        tRsCoinSilver.push_back(tRCoin);
        resources.push_back(tRCoin);
    }
    y = 2;
    for(int x = 0; x < 7; ++x) {
        auto tRCoin = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                     x * coinSize.x,
                                                                     y * coinSize.y, coinSize.x,
                                                                     coinSize.y);
        tRsCoinBronze.push_back(tRCoin);
        resources.push_back(tRCoin);
    }
    for(int x = 5; x >= 1; --x) {
        auto tRCoin = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                     x * coinSize.x,
                                                                     y * coinSize.y, coinSize.x,
                                                                     coinSize.y);
        tRsCoinBronze.push_back(tRCoin);
        resources.push_back(tRCoin);
    }
    Vec2<int> coinDiamondSize(16, 16);
    y = 3;
    for(int x = 0; x < 5; ++x) {
        auto tRCoin = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                     x * coinDiamondSize.x,
                                                                     y * coinDiamondSize.y, coinDiamondSize.x,
                                                                     coinDiamondSize.y);
        tRsCoinDiamond.push_back(tRCoin);
        resources.push_back(tRCoin);
    }
    Vec2<int> coinPickSize(16, 16);
    y = 4;
    for(int x = 0; x < 8; ++x) {
        auto tRCoinPick = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                         x * coinPickSize.x,
                                                                         y * coinPickSize.y, coinPickSize.x,
                                                                         coinPickSize.y);
        tRsCoinPickGold.push_back(tRCoinPick);
        resources.push_back(tRCoinPick);

        tRCoinPick = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                    x * coinPickSize.x,
                                                                    (y + 1) * coinPickSize.y, coinPickSize.x,
                                                                    coinPickSize.y);
        tRsCoinPickSilver.push_back(tRCoinPick);
        resources.push_back(tRCoinPick);

        tRCoinPick = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                    x * coinPickSize.x,
                                                                    (y + 2) * coinPickSize.y, coinPickSize.x,
                                                                    coinPickSize.y);
        tRsCoinPickBronze.push_back(tRCoinPick);
        resources.push_back(tRCoinPick);

        tRCoinPick = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTCoin.get(),
                                                                    x * coinPickSize.x,
                                                                    (y + 3) * coinPickSize.y, coinPickSize.x,
                                                                    coinPickSize.y);
        tRsCoinPickDiamond.push_back(tRCoinPick);
        resources.push_back(tRCoinPick);
    }

    Vec2<int> elixirSize(16, 16);
    y = 0;
    for(int x = 0; x < 6; ++x) {
        auto tRElixir = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTEnergy.get(),
                                                                       x * elixirSize.x,
                                                                       y * elixirSize.y, elixirSize.x,
                                                                       elixirSize.y);
        tRsElixir.push_back(tRElixir);
        resources.push_back(tRElixir);
    }
    Vec2<int> elixirPickSize(16, 16);
    y = 1;
    for(int x = 0; x < 11; ++x) {
        auto tRElixirPick = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTEnergy.get(),
                                                                           x * elixirPickSize.x,
                                                                           y * elixirPickSize.y, elixirPickSize.x,
                                                                           elixirPickSize.y);
        tRsElixirPick.push_back(tRElixirPick);
        resources.push_back(tRElixirPick);
    }

    Vec2<int> cherrySize(16, 16);
    y = 4;
    for(int x = 0; x < 4; ++x) {
        auto tRCherry = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTEnergy.get(),
                                                                       x * cherrySize.x,
                                                                       y * cherrySize.y, cherrySize.x,
                                                                       cherrySize.y);
        tRsCherry.push_back(tRCherry);
        resources.push_back(tRCherry);
    }
    Vec2<int> cherryPickSize(16, 16);
    y = 5;
    for(int x = 0; x < 11; ++x) {
        auto tRCherryPick = std::make_shared<AndroidOpenGLTextureRegion2D>(app, aOGLTEnergy.get(),
                                                                           x * cherryPickSize.x,
                                                                           y * cherryPickSize.y, cherryPickSize.x,
                                                                           cherryPickSize.y);
        tRsCherryPick.push_back(tRCherryPick);
        resources.push_back(tRCherryPick);
    }

    // quad2D texture
    qGameGB = std::make_shared<AndroidOpenGLQuadTexture2D>();
    resources.push_back(qGameGB);

    // quad2D texture region
    qTRBird = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRBird);
    qTRWall = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRWall);
    qTRGrassDirt1x1 = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRGrassDirt1x1);
    qTRDirt1x1 = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRDirt1x1);
    qTRCoinGold = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRCoinGold);
    qTRCoinSilver = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRCoinSilver);
    qTRCoinBronze = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRCoinBronze);
    qTRCoinDiamond = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRCoinDiamond);
    qTRAnimationEnd = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRAnimationEnd);
    qTRElixir = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRElixir);
    qTRCherry = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRCherry);
    qTRImageView = std::make_shared<AndroidOpenGLQuadTextureRegion2D>();
    resources.push_back(qTRImageView);

    // shader
    shScene = std::make_shared<AndroidOpenGLTexture2DShader>(
            std::make_shared<AndroidOpenGLShader>(app, Assets::PATH_SHADER + "scene.vs", true,
                                                  GL_VERTEX_SHADER),
            std::make_shared<AndroidOpenGLShader>(app, Assets::PATH_SHADER + "scene.fs", true,
                                                  GL_FRAGMENT_SHADER));
    resources.push_back(shScene);

    // sound
    sFlapWings = std::make_shared<AndroidOpenSLESSound>(app,
                                                        Assets::PATH_SOUND + "bird_jump.wav",
                                                        true);
    resources.push_back(sFlapWings);
    sFlapWings->setVolume(0.60f);
    sGoalReach = std::make_shared<AndroidOpenSLESSound>(app,
                                                        Assets::PATH_SOUND + "goal.wav",
                                                        true);
    resources.push_back(sGoalReach);
    sGoalReach->setVolume(0.20f);
    sBirdHit = std::make_shared<AndroidOpenSLESSound>(app,
                                                      Assets::PATH_SOUND + "bird_crash.wav",
                                                      true);
    resources.push_back(sBirdHit);
    sBirdHit->setVolume(0.30f);
    sCoin = std::make_shared<AndroidOpenSLESSound>(app,
                                                   Assets::PATH_SOUND + "coin.wav",
                                                   true);
    resources.push_back(sCoin);
    sCoin->setVolume(0.25f);
    sCoin2 = std::make_shared<AndroidOpenSLESSound>(app,
                                                    Assets::PATH_SOUND + "coin2.wav",
                                                    true);
    resources.push_back(sCoin2);
    sCoin2->setVolume(0.25f);
    sCoin3 = std::make_shared<AndroidOpenSLESSound>(app,
                                                    Assets::PATH_SOUND + "coin3.wav",
                                                    true);
    resources.push_back(sCoin3);
    sCoin3->setVolume(0.25f);
    sCoin4 = std::make_shared<AndroidOpenSLESSound>(app,
                                                    Assets::PATH_SOUND + "coin4.wav",
                                                    true);
    resources.push_back(sCoin4);
    sCoin4->setVolume(0.25f);
    sEnergyGainElixir = std::make_shared<AndroidOpenSLESSound>(app,
                                                    Assets::PATH_SOUND + "energy_gain_elixir.wav",
                                                    true);
    resources.push_back(sEnergyGainElixir);
    sEnergyGainElixir->setVolume(0.75f);
    sEnergyGainCherry = std::make_shared<AndroidOpenSLESSound>(app,
                                                         Assets::PATH_SOUND + "energy_gain_cherry.wav",
                                                         true);
    resources.push_back(sEnergyGainCherry);
    sEnergyGainCherry->setVolume(0.75f);

    // music
    mGame = std::make_shared<AndroidOpenSLESMusic>(app, Assets::PATH_MUSIC + "game.wav", true);
    resources.push_back(mGame);
}
