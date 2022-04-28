#include "Animation.h"

bool colCmp(Uint8 col1, Uint8 col2) {
    return col1 > col2;
}

colorAnimation::colorAnimation(SDL_Color *color, SDL_Color from, SDL_Color to, double seconds) {
    col = color;
    col1 = from;
    col2 = to;
    duration = seconds;

    if (duration > 3) duration = 3;
}

bool colorAnimation::animate(int frame) {
    if (isAnimate) {
        if (!reversed) {
            if (col->r == col2.r && col->g == col2.g && col->b == col2.b) {
                stop();
                return false;
            }
            col->r = frame * col2.r / (duration * 33.3);
            col->g = frame * col2.g / (duration * 33.3);
            col->b = frame * col2.b / (duration * 33.3);
        } else {
            if (col->r == col1.r && col->g == col1.g && col->b == col1.b) {
                stop();
                return false;
            }
            col->r = frame * col1.r / (duration * 33.3);
            col->g = frame * col1.g / (duration * 33.3);
            col->b = frame * col1.b / (duration * 33.3);
        }
        return true;
    }

    return false;
}

void colorAnimation::play() {
    isAnimate = true;
}

void colorAnimation::stop() {
    isAnimate = false;
}

intAnimation::intAnimation(int *_value, int _from, int _to, int duration_frames, int bAcceleration, int eAcceleration) {
    if (_from > _to) incRange = false;
    if (duration_frames <= 0) throw "invalid duration of animation";

    value = _value;
    from = _from;
    to = _to;
    duration = duration_frames;
    bAcc = bAcceleration;
    eAcc = eAcceleration;
    counter = 0;
}

void intAnimation::setRange(int _from, int _to) {
    if (_from > _to) {
        incRange = false;
    } else {
        incRange = true;
    }
    from = _from;
    to = _to;
}

void intAnimation::setDuration(int _duration) {
    if (_duration <= 0) throw "invalid duration of animation";
    duration = _duration;
}

void intAnimation::setAccelerations(int bAcceleration, int eAcceleration) {
    bAcc = bAcceleration;
    eAcc = eAcceleration;
}

bool intAnimation::animate(int frame) {
    if (animating) {
        if (reversed) {
            *value += counter * to / duration + ((*value / 20) * (bAcc + 1));
            if (incRange) {
                if (*value >= to) {
                    *value = to;
                    requeresReverse = true;
                    stop();
                }
            } else {
                if (*value <= to) {
                    *value = to;
                    requeresReverse = true;
                    stop();
                }
            }
        } else {
            *value -= counter * to / duration + ((*value / 20) * (eAcc + 1));
            if (incRange) {
                if (*value <= from) {
                    *value = from;
                    requeresReverse = false;
                    stop();
                }
            } else {
                if (*value >= from) {
                    *value = from;
                    requeresReverse = false;
                    stop();
                }
            }
        }
        if (everyFrame != nullptr) everyFrame();
        counter++;
        return true;
    }
    return false;
}

void intAnimation::stop() {
    if (afterStopped != nullptr) afterStopped();
    counter = 0;
    animating = false;
}

intAnimation::~intAnimation() {
    delete this;
}

colorAnimation::~colorAnimation() {
    delete this;
}
