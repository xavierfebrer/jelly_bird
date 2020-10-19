#ifndef SCREEN_H
#define SCREEN_H

#include "BaseInclude.h"
#include "ViewManager.h"

template <typename G>
class Screen {
public:
    Screen(G & game);
    virtual ~Screen();

    virtual void create() = 0;
    virtual void resize(double width, double height) = 0;
    virtual void resume() = 0;
    virtual void update(double deltaTime) = 0;
    virtual void render(double deltaTime) = 0;
    virtual void pause() = 0;
protected:
    G & game;
    ViewManager<G> viewManager;
};

template <typename G>
Screen<G>::Screen(G & game) : game(game), viewManager(ViewManager(game)) {
}

template <typename G>
Screen<G>::~Screen() {
}

#endif