#include "../../include/AndroidAssets.h"
#include "../../../core/include/AssetGroup.h"

const std::string Assets::PATH_ASSETS = "";
const std::string Assets::PATH_IMAGE = PATH_ASSETS + "image/";
const std::string Assets::PATH_AUDIO = PATH_ASSETS + "audio/";
const std::string Assets::PATH_MUSIC = PATH_AUDIO + "music/";
const std::string Assets::PATH_SOUND = PATH_AUDIO + "sound/";
const std::string Assets::PATH_SHADER = PATH_ASSETS + "shader/";

AndroidAssets::AndroidAssets(android_app* app) : Assets(), app(app) {
}

AndroidAssets::~AndroidAssets() {
}

BaseComponentReadiness AndroidAssets::isReady() {
    return isInitialized() ? BaseComponentReadiness::READY : BaseComponentReadiness::NOT_READY;
}
