#ifndef ASSET_GROUP_H
#define ASSET_GROUP_H

#include "BaseInclude.h"
#include "Assets.h"
#include "Resource.h"

class AssetGroup {
public:
    AssetGroup();
    virtual ~AssetGroup();

    virtual bool isLoaded();
    virtual bool load() = 0;
    virtual bool unLoad() = 0;
protected:
    bool loaded;

    std::vector<std::shared_ptr<Resource>> resources;
};

#endif