#include "..\..\include\AssetGroup.h"

AssetGroup::AssetGroup() : loaded(false) {
}

AssetGroup::~AssetGroup() {
}

bool AssetGroup::isLoaded() {
    return loaded;
}
