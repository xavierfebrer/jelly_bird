#include "../../include/AndroidLogoAssets.h"

AndroidLogoAssets::AndroidLogoAssets(android_app* app) : LogoAssets(), app(app) {
}

AndroidLogoAssets::~AndroidLogoAssets() {
    unLoad();
}

bool AndroidLogoAssets::load() {
    if(!loaded) {
        std::cout << "---> load LogoAssets" << std::endl;

        for(auto & resource : resources) {
            resource->load();
        }
        loaded = true;
    }
    return loaded;
}

bool AndroidLogoAssets::unLoad() {
    if(loaded) {
        std::cout << "---> unLoad LogoAssets" << std::endl;

        for(auto & resource : resources) {
            resource->unLoad();
        }
        loaded = false;
    }
    return !loaded;
}
