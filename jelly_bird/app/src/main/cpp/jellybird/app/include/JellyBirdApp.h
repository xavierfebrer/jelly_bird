#ifndef JELLY_BIRD_APP_H
#define JELLY_BIRD_APP_H

#include "GameApp.h"

template<class G, class S>
class JellyBirdApp : public GameApp<G, S> {
public:
    JellyBirdApp(std::unique_ptr<G> game, S & initState);
    virtual ~JellyBirdApp() override;
};

template<class G, class S>
JellyBirdApp<G, S>::JellyBirdApp(std::unique_ptr<G> game, S & initState) : GameApp<G, S>(std::move(game), initState) {
}

template<class G, class S>
JellyBirdApp<G, S>::~JellyBirdApp() {
}


#endif
