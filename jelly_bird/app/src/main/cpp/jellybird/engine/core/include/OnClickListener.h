#ifndef ON_CLICK_LISTENER_H
#define ON_CLICK_LISTENER_H

#include "BaseInclude.h"
#include "View.h"

class OnClickListener {
public:
    OnClickListener() {}

    virtual ~OnClickListener() {}

    virtual void onClickDown(View & view) = 0;
    virtual void onClickUp(View & view) = 0;
};

#endif