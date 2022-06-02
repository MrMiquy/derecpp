#include "Border.h"

enum Alignment {
    Horizontal,
    Vertical,
};

class Scrollbar : public Border {
public:
    void setAlignment(Alignment alignment);
    void setRange(int min, int max);
    void setMin(int min);
    void setMax(int max);
    void setValue(int* valueToScroll);

    Alignment getAlignment();
    SDL_Point getRange();
    int getMin();
    int getMax();
    int getValue();

protected:
    Alignment alignment = Vertical;
    int min, max;
    int* value;
    SDL_Color color = {50, 50, 50, 50};
};
