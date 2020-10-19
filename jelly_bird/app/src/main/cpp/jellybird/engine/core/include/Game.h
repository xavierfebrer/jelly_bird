#ifndef GAME_H
#define GAME_H

#include "BaseInclude.h"
#include "Vec2.h"
#include "Rect.h"

template<class S>
class Game {
public:
    Game();
    virtual ~Game();

    virtual bool create() = 0;
    virtual void loop() = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
    virtual void resize(double width, double height) = 0;
    virtual void setScreen(std::unique_ptr<S> newScreen) = 0;
    virtual void exit() = 0;
};

template<class S>
Game<S>::Game() {
}

template<class S>
Game<S>::~Game() {
}

#endif