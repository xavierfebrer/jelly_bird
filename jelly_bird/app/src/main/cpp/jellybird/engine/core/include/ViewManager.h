#ifndef VIEW_MANANGER_H
#define VIEW_MANANGER_H

#include "BaseInclude.h"
#include "View.h"
#include "PointerEventInfo.h"
#include "Hack3dEngine.h"

template <typename G>
class ViewManager {
public:
    ViewManager(G & game);
    virtual ~ViewManager();

    void addView(const std::shared_ptr<View<G>> & view);
    int removeView(const std::shared_ptr<View<G>> & view);
    void clear();
    void resume();
    void update(double deltaTime, Camera & camera);
    void render(double deltaTime, Camera & camera, Texture2DShader & shader);
    void resize(double width, double height);
    void pause();
protected:
    G & game;
    std::vector<std::shared_ptr<View<G>>> views;
private:
    std::vector<std::unique_ptr<PointerEventInfo>> pointerEvents;

    void updateInput(double deltaTime, Camera & camera);
    void updatePointerEvents(double deltaTime, Camera & camera);
    void sendPointerEventData(double deltaTime);
    void updateState(double deltaTime);
};

template <typename G>
ViewManager<G>::ViewManager(G & game) : game(game) {
    for(int i = 0; i < Input::MAX_POINTERS; i++) {
        pointerEvents.push_back(std::make_unique<PointerEventInfo>(i));
    }
}

template <typename G>
ViewManager<G>::~ViewManager() {
    clear();
}

template <typename G>
void ViewManager<G>::addView(const std::shared_ptr<View<G>> & view) {
    views.push_back(view);
}

template <typename G>
int ViewManager<G>::removeView(const std::shared_ptr<View<G>> & view) {
    int deletedPointer = 0;
    size_t sizeCurrentViews = views.size();
    if(sizeCurrentViews > 0) {
        for(size_t i = sizeCurrentViews - 1; i >= 0; i--) {
            if(views[i] == view) {
                views.erase(views.begin() + i);
                ++deletedPointer;
            }
        }
    }
    return deletedPointer;
}

template <typename G>
void ViewManager<G>::clear() {
    views.clear();
}

template <typename G>
void ViewManager<G>::resume() {
    for(std::shared_ptr<View<G>> view : views) view->resume();
}

template <typename G>
void ViewManager<G>::update(double deltaTime, Camera & camera) {
    updateInput(deltaTime, camera);
    updateState(deltaTime);
}

template <typename G>
void ViewManager<G>::updateInput(double deltaTime, Camera & camera) {
    updatePointerEvents(deltaTime, camera);
    sendPointerEventData(deltaTime);
}

template <typename G>
void ViewManager<G>::updatePointerEvents(double deltaTime, Camera & camera) {
    Vec2<int> windowSize = Hack3dEngine::get().graphics().getWindowSize();
    for(int i = 0; i < pointerEvents.size(); ++i) {
        PointerEventInfo & pointerEventInfo = *pointerEvents[i];
        if(Hack3dEngine::get().input().isPointerPressed(i)) {
            if(pointerEventInfo.pointerEvent == PointerEvent::IDLE) {
                pointerEventInfo.pointerEvent = PointerEvent::DOWN;
            } else {
                pointerEventInfo.pointerEvent = PointerEvent::MOVE;
            }
        } else {
            if(pointerEventInfo.pointerEvent != PointerEvent::IDLE &&
               pointerEventInfo.pointerEvent != PointerEvent::UP) {
                pointerEventInfo.pointerEvent = PointerEvent::UP;
            } else {
                pointerEventInfo.pointerEvent = PointerEvent::IDLE;
            }
        }
        const PointerInfo & pointerPos = Hack3dEngine::get().input().getPointerInfo(i);
        pointerEventInfo.xScreen = pointerPos.x;
        pointerEventInfo.yScreen = pointerPos.y;

        Vec2<> worldPos = camera.screenToWorldSpaceCoords(Vec2<>(pointerEventInfo.xScreen, pointerEventInfo.yScreen), windowSize);

        pointerEventInfo.xViewCamera = worldPos.x;
        pointerEventInfo.yViewCamera = worldPos.y;
    }
}

template <typename G>
void ViewManager<G>::sendPointerEventData(double deltaTime) {
    bool consumed;
    long sizeCurrentViews = views.size();
    if(sizeCurrentViews > 0) {
        for(long i = 0; i < pointerEvents.size(); ++i) {
            PointerEventInfo & pointerEventInfo = *pointerEvents[i];
            consumed = false;
            for(long j = sizeCurrentViews - 1; j >= 0; --j) {
                if(views[j]->input(deltaTime, pointerEventInfo, consumed)) {
                    consumed = true;
                }
            }
        }
    }
}

template <typename G>
void ViewManager<G>::updateState(double deltaTime) {
    for(std::shared_ptr<View<G>> view : views) view->update(deltaTime);
}

template <typename G>
void ViewManager<G>::render(double deltaTime, Camera & camera, Texture2DShader & shader) {
    for(std::shared_ptr<View<G>> view : views) view->render(deltaTime, camera, shader);
}

template <typename G>
void ViewManager<G>::resize(double width, double height) {
    for(std::shared_ptr<View<G>> view : views) view->resize(width, height);
}

template <typename G>
void ViewManager<G>::pause() {
    for(std::shared_ptr<View<G>> view : views) view->pause();
}


#endif