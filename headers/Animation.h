#include "math.h"

class Animation {
public:
    Animation();
    ~Animation();

    void setDuration(unsigned int duration);
    void setAcceleration(int beginAcceleration, int endAcceleration);
    void setRange(int from, int to);
    void setValue(int* valueToAnimate);

    unsigned int getDuration();
    bool isAnimating();
    void stop();
    void play();
    bool animate();

private:
    unsigned int counter = 1;
    unsigned int duration = 0;      // ms
    int beginAcceleration = 1;
    int endAcceleration = 1;
    int from;
    int to;
    int* value;                 // value to animate

    bool reversed = false;
    bool animating = false;
};
