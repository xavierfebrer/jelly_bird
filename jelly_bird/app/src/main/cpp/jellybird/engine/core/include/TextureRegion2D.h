#ifndef TEXTURE_REGION_2D_H
#define TEXTURE_REGION_2D_H

#include "Texture2D.h"

class TextureRegion2D : public Resource {
public:
    TextureRegion2D(Texture2D * texture2D, int x, int y, int w, int h);
    TextureRegion2D(Texture2D * texture2D, const Rect<int> & region);
    virtual ~TextureRegion2D();

    virtual void activeBind();
    virtual Texture2D * getTexture2D();
    virtual Rect<int> getRegion();
protected:
    Texture2D * texture2D;
    Rect<int> region;
};

#endif