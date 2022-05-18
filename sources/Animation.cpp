#include "../headers/Animation.h"

Animation::Animation() {
}

Animation::~Animation() {
}

bool Animation::animate() {
    if (animating) {
        if (reversed == false) {
            *value = counter + from;
            if (*value >= to) stop();
        } else {
            *value = -counter + from;
            if (*value <= to) stop();
        }
        counter++;
        return true;
    }
    return false;
}

void Animation::stop() {
    from = to;
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
    duration = _duration;
}

unsigned int Animation::getDuration() {
    return duration;
}

void Animation::setRange(int _from, int _to) {
    if (_from > _to) {
        reversed = true;
    } else {
        reversed = false;
    }
    from = _from;
    to = _to;
}

void Animation::setValue(int *valueToAnimate) {
    value = valueToAnimate;
}
