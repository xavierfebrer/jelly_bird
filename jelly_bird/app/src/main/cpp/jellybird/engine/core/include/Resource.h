#ifndef RESOURCE_H
#define RESOURCE_H

#include "BaseInclude.h"

class Resource {
public:
    Resource();
    virtual ~Resource();

    virtual bool isLoaded();
    virtual bool load() = 0;
    virtual bool unLoad() = 0;
protected:
    bool loaded;
};

#endif