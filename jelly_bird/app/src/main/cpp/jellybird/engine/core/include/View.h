#ifndef VIEW_H
#define VIEW_H

#include "BaseInclude.h"
#include "Rect.h"
#include "PointerEventInfo.h"
#include "Vec2.h"
#include "Util.h"
#include "Texture2DShader.h"
#include "Camera.h"

template <typename G>
class View {
public:
    static const double MIN_ALPHA;
    static const double MAX_ALPHA;

    View(G & game, const Rect<> & bounds);
    virtual ~View();

    virtual void resume() = 0;
    virtual bool input(double deltaTime, const PointerEventInfo & pointerEventInfo, bool consumed) = 0;
    virtual void update(double deltaTime);
    virtual void render(double deltaTime, Camera & camera, Texture2DShader & shader) = 0;
    virtual void resize(double width, double height) = 0;
    virtual void pause() = 0;
    virtual const bool isEnabled();
    virtual void setEnabled(bool enabled);
    virtual const double getAlpha();
    virtual void setAlpha(double alpha);
    virtual void incAlpha(double deltaAlpha);
    virtual const double getX();
    virtual void setX(double x);
    virtual void incX(double deltaX);
    virtual const double getY();
    virtual void setY(double y);
    virtual void incY(double deltaY);
    virtual void setPos(double x, double y);
    virtual void setPos(const Vec2<> & pos);
    virtual void incPos(double deltaX, double deltaY);
    virtual const double getWidth();
    virtual void setWidth(double width);
    virtual void incWidth(double deltaWidth);
    virtual const double getHeight();
    virtual void setHeight(double height);
    virtual void incHeight(double deltaHeight);
    virtual void setSize(double width, double height);
    virtual void setSize(const Vec2<> & size);
    virtual void set(double x, double y, double width, double height);
    virtual void set(const Vec2<> & pos, const Vec2<> & size);
    virtual void set(const Rect<> & bounds);
    virtual const Rect<> & getBounds();
protected:
    G & game;
    Rect<> bounds;
private:
    bool enabled;
    double alpha;
};

template <typename G>
const double View<G>::MIN_ALPHA = 0;
template <typename G>
const double View<G>::MAX_ALPHA = 1;

template <typename G>
View<G>::View(G & game, const Rect<> & bounds) : game(game), bounds(bounds) {
    setEnabled(true);
    setAlpha(View<G>::MAX_ALPHA);
}

template <typename G>
View<G>::~View() {
}

template <typename G>
void View<G>::update(double deltaTime) {
}

template <typename G>
const bool View<G>::isEnabled() {
    return enabled;
}

template <typename G>
void View<G>::setEnabled(bool enabled) {
    this->enabled = enabled;
}

template <typename G>
const double View<G>::getAlpha() {
    return alpha;
}

template <typename G>
void View<G>::setAlpha(double alpha) {
    this->alpha = Util::minMax(alpha, View<G>::MIN_ALPHA, View<G>::MAX_ALPHA);
}

template <typename G>
void View<G>::incAlpha(double deltaAlpha) {
    setAlpha(getAlpha() + deltaAlpha);
}

template <typename G>
const double View<G>::getX() {
    return this->bounds.x;
}

template <typename G>
void View<G>::setX(double x) {
    this->bounds.x = x;
}

template <typename G>
void View<G>::incX(double deltaX) {
    setX(getX() + deltaX);
}

template <typename G>
const double View<G>::getY() {
    return this->bounds.y;
}

template <typename G>
void View<G>::setY(double y) {
    this->bounds.y = y;
}

template <typename G>
void View<G>::incY(double deltaY) {
    setY(getY() + deltaY);
}

template <typename G>
void View<G>::setPos(double x, double y) {
    setX(x);
    setY(y);
}

template <typename G>
void View<G>::setPos(const Vec2<> & pos) {
    setX(pos.x);
    setY(pos.y);
}

template <typename G>
void View<G>::incPos(double deltaX, double deltaY) {
    setPos(getX() + deltaX, getY() + deltaY);
}

template <typename G>
const double View<G>::getWidth() {
    return this->bounds.w;
}

template <typename G>
void View<G>::setWidth(double w) {
    this->bounds.w = w;
}

template <typename G>
void View<G>::incWidth(double deltaW) {
    setWidth(getWidth() + deltaW);
}

template <typename G>
const double View<G>::getHeight() {
    return this->bounds.h;
}

template <typename G>
void View<G>::setHeight(double h) {
    this->bounds.h = h;
}

template <typename G>
void View<G>::incHeight(double deltaH) {
    setHeight(getHeight() + deltaH);
}

template <typename G>
void View<G>::setSize(double w, double h) {
    setWidth(w);
    setHeight(h);
}

template <typename G>
void View<G>::setSize(const Vec2<> & size) {
    setWidth(size.x);
    setHeight(size.y);
}

template <typename G>
void View<G>::set(double x, double y, double w, double h) {
    setPos(x, y);
    setPos(w, h);
}

template <typename G>
void View<G>::set(const Vec2<> & pos, const Vec2<> & size) {
    setPos(pos);
    setSize(size);
}

template <typename G>
void View<G>::set(const Rect<> & bounds) {
    this->bounds = bounds;
}

template <typename G>
const Rect<> & View<G>::getBounds() {
    return bounds;
}

#endif