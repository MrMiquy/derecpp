#include "Widget.h"
#include "Parent.h"
#include <vector>

class Border : public Widget, public Colorize, public Parent {
public:
    Border();
    ~Border();

    void render();
private:

};
