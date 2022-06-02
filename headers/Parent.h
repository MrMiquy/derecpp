#include "Widget.h"
#include <vector>
#ifndef __PARENT
#define __PARENT

class Parent {
public:
    virtual void addChild(Widget* child);
    void fixChildrenPos(bool value);

protected:
    bool isFixed = true;
    std::vector<Widget*> children;
};

#endif // __PARENT
