#include "Widget.h"
#include <math.h>

class Ellipse : public Widget, public Colorize {
public:
    Ellipse();
    ~Ellipse();

    void render();
};
