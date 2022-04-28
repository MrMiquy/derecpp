#ifndef __ANIMATION__
#include "Widget.h"

class colorAnimation {
public:
    SDL_Color *col;
    SDL_Color col1, col2;
    double duration;

    colorAnimation(SDL_Color *color, SDL_Color from, SDL_Color to, double seconds);
    ~colorAnimation();

    void reverse();
    bool isReversed();

    bool animate(int frame);
    void play();
    void stop();

private:
    bool reversed = false;
    bool isAnimate = false;
};

class intAnimation {
public:
    intAnimation(int *_value, int _from, int _to, int duration_frames, int bAcceleration = 0, int eAcceleration = 0);
    ~intAnimation();

    void setDuration(int _duration);
    void setRange(int _from, int _to);
    void setIncRange(bool inc) {incRange = inc;}
    void setAccelerations(int bAcceleration, int eAcceleration);
    void setFrameFunc(std::function<void()> func) { everyFrame = func; }
    void setStoppedFunc(std::function<void()> func) { afterStopped = func; }

    void reverse() { reversed = !reversed; }
    bool animate(int frame);

    void play() { animating = true; }
    void stop();
    void wait(bool _value = true) { waitAnim = _value; }

    bool isWaiting() { return waitAnim; }
    bool isIncRange() { return incRange; }
    bool isAnimating() { return animating; }
    bool isRequeresReverse() { return requeresReverse; }
    bool isReversed() { return reversed; }

private:
    int* value;
    int duration, counter;
    int from, to, bAcc, eAcc;
    bool animating = false;
    bool waitAnim = true;
    bool reversed = true;
    bool incRange = true;
    bool requeresReverse = false;
    std::function<void()> everyFrame;
    std::function<void()> afterStopped;
};

#define __ANIMATION__
#endif
