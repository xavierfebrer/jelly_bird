#ifndef ANDROIDASSETS_H
#define ANDROIDASSETS_H

#include "../../core/include/Assets.h"
#include <android_native_app_glue.h>

class AndroidAssets : public Assets {
public:
    android_app* app;

    AndroidAssets(android_app* app);
    virtual ~AndroidAssets() override;

    virtual BaseComponentReadiness isReady() override;
protected:
    std::map<std::string, std::map<std::string, std::shared_ptr<Resource>>> assetGroups;
};

#endif