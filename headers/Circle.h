#include "Widget.h"

class Circle : public Widget, public Colorize {
public:
    Circle();
    ~Circle();

    void render();

    void setCentre(int32_t centreX, int32_t centreY);
    void setRadius(int32_t radius);

    int32_t getX();
    int32_t getY();
    int32_t getRadius();
    int32_t getDiameter();

    void setFill(bool value);
    bool isFill();

protected:
    int32_t x, y;
    int32_t radius, diameter;
    bool fill = true;
};
