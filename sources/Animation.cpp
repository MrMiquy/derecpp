#include "../headers/Animation.h"

bool intAnimation::animate() {
    if (animating) {
        if (from <= to) {
            if (*value >= to) {
                stop();
                *value = to;
            } else {
                *value = counter * to / duration / (to / duration) / duration + from;
            }
        } else {
            if (*value <= to) {
                stop();
                *value = to;
            } else {
                *value = -(counter * to / duration / (to / duration) / duration) + from;
            }
        }
        counter++;
        return true;
    }
    return false;
}

bool uInt8Animation::animate() {
    if (animating) {
        if (from <= to) {
            if (*value >= to) {
                stop();
                *value = to;
            } else {
                *value = counter * to / duration / (to / duration) / duration + from;
            }
        } else {
            if (*value <= to) {
                stop();
                *value = to;
            } else {
                *value = -(counter * to / duration / (to / duration) / duration) + from;
            }
        }
        counter++;
        return true;
    }
    return false;
}

void ColorAnimation::setRange(SDL_Color _from, SDL_Color _to) {
    from = _from;
    to = _to;
    r.setRange(from.r, to.r);
    g.setRange(from.g, to.g);
    b.setRange(from.b, to.b);
    a.setRange(from.a, to.a);
}

void ColorAnimation::setDuration(unsigned int ms) {
    duration = ms;
    r.setDuration(ms);
    g.setDuration(ms);
    b.setDuration(ms);
    a.setDuration(ms);
}

void ColorAnimation::setValue(SDL_Color* v) {
    value = v;
    r.setValue(&value->r);
    g.setValue(&value->g);
    b.setValue(&value->b);
    a.setValue(&value->a);
}

void ColorAnimation::play() {
    animating = true;
    r.play();
    g.play();
    b.play();
    a.play();
}

void ColorAnimation::stop() {
    counter = 1;
    animating = false;
    r.stop();
    g.stop();
    b.stop();
    a.stop();
}

bool ColorAnimation::animate() {
    if (animating) {
        bool neededRender = false;

        if (r.animate()) neededRender = true;
        if (g.animate()) neededRender = true;
        if (b.animate()) neededRender = true;
        if (a.animate()) neededRender = true;
        printf("color render: %d\n", neededRender);

        return animating = neededRender;
    }
    return false;
}
