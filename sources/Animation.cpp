#include "../headers/Animation.h"

Animation::Animation() {
}

Animation::~Animation() {
}


bool Animation::animate() {
    if (animating) {
        *value = counter * to / duration + from;
        if (*value >= to) stop();
        counter++;
        return true;
    }
    return false;
}


void Animation::stop() {
    from = to;
    reset();
}

void Animation::reset() {
    counter = 1;
    animating = false;
}

void Animation::play() {
    if (animating == false) {
        *value = from;
        animating = true;
    }
}

bool Animation::isAnimating() {
    return animating;
}

void Animation::setAcceleration(int bAcc, int eAcc) {
    beginAcceleration = bAcc;
    endAcceleration = eAcc;
}

void Animation::setDuration(unsigned int _duration) {
    if (_duration == 0) duration++;
    duration = ++_duration;
}

unsigned int Animation::getDuration() {
    return duration;
}

void Animation::setRange(int _from, int _to) {
    if (_from > _to) reversed = true;
    from = _from;
    to = _to;
}

void Animation::setValue(int *valueToAnimate) {
    value = valueToAnimate;
}

void Animation::setCycled(bool isCycled) {
    cycled = isCycled;
}
