#include "../headers/Scrollbar.h"

void Scrollbar::setAlignment(Alignment _alignment) {
    alignment = _alignment;
}

void Scrollbar::setRange(int _min, int _max) {
    min = _min;
    max = _max;
}

void Scrollbar::setMin(int _min) {
    min = _min;
}

void Scrollbar::setMax(int _max) {
    max = _max;
}

void Scrollbar::setValue(int* valueToScroll) {
    value = valueToScroll;
}

Alignment Scrollbar::getAlignment() {
    return alignment;
}

SDL_Point Scrollbar::getRange() {
    return {min, max};
}

int Scrollbar::getMin() {
    return min;
}

int Scrollbar::getMax() {
    return max;
}

int Scrollbar::getValue() {
    return *value;
}
