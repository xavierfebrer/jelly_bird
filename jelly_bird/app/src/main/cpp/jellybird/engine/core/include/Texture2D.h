#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Resource.h"
#include "Vec2.h"
#include "Rect.h"
#include "Util.h"

class Texture2D : public Resource {
public:
    Texture2D(const std::string & path);
    virtual ~Texture2D();

    virtual void activeBind() = 0;
    virtual std::string getPath();
    virtual Vec2<int> getSize();
protected:
    std::string path;
    Vec2<int> size;
};

#endif