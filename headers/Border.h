#include "Widget.h"
#include "Parent.h"
#include <vector>

#ifndef __BORDER
#define __BORDER

class Border : public Widget, public Colorize, public Parent {
public:
    Border();
    ~Border();

    void render();

private:

};

#endif // __BORDER
