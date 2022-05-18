#include "Widget.h"
#include <vector>
#ifndef PARENT
#define PARENT

class Parent {
public:
    Parent();
    ~Parent();

    void addChild(Widget* child);

protected:
    std::vector<Widget*> children;
};

#endif
