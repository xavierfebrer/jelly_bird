#ifndef GAME_APP_H
#define GAME_APP_H

#include "App.h"
#include "../../engine/core/include/BaseInclude.h"
#include "../../game/core/include/JellyBirdGame.h"

enum class GameAppState {
    None, Initialized, Resumed, Looping, Paused, Destroyed
};

template<class G, class S>
class GameApp : App {
public:
    std::unique_ptr<G> game;
    S state;

    GameApp(std::unique_ptr<G> game, S & initState);
    virtual ~GameApp() override;
};

template<class G, class S>
GameApp<G, S>::GameApp(std::unique_ptr<G> game, S & initState) : App(), game(std::move(game)), state(initState) {
}

template<class G, class S>
GameApp<G, S>::~GameApp() {
}

#endif