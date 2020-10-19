#include "../../../core/include/Resource.h"

Resource::Resource() : loaded(false) {
}

Resource::~Resource() {
}

bool Resource::isLoaded() {
    return loaded;
}
